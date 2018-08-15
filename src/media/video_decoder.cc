#include "content/eglcontent/media/video_decoder.h"

namespace media {

  EGLContentVideoDecoder::EGLContentVideoDecoder(
    EGLContent::VideoDecoderDelegate* delegate,
    scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
    gpu::GpuCommandBufferStub* stub)
    : delegate_(delegate),
      task_runner_(task_runner),
      command_buffer_stub_(stub) {
  }

  EGLContentVideoDecoder::~EGLContentVideoDecoder() {
  }

  std::string EGLContentVideoDecoder::GetDisplayName() const {
  }

  void EGLContentVideoDecoder::Initialize(const VideoDecoderConfig& config,
					  bool low_delay,
					  CdmContext* cdm_context,
					  const InitCB& init_cb,
					  const OutputCB& output_cb) {
    has_key_ = false;
    resetting_ = false;
    pending_decode_.Reset();

    config_ = config;
    output_cb_ = output_cb;

    if (cdm_context) {
      decryptor_ = cdm_context->GetDecryptor();
      decryptor_->RegisterNewKeyCB(
	Decryptor::kVideo,
	base::Bind(&EGLContentVideoDecoder::OnDecryptionKeyAdded, this));
    } else {
      decryptor_ = NULL;
    }

    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&EGLContentVideoDecoder::InitializeTask,
		 this, config, init_cb));
  }

  void EGLContentVideoDecoder::Decode(const scoped_refptr<DecoderBuffer>& buffer,
				      const DecodeCB& decode_cb) {
    if (resetting_) {
      decode_cb.Run(DecodeStatus::ABORTED);
      return;
    }

    base::Closure callback = base::Bind(
      &EGLContentVideoDecoder::DecodeTask, this, buffer, decode_cb);

    if (decryptor_) {
      callback = base::Bind(&EGLContentVideoDecoder::DecryptTask,
			    this, buffer, decode_cb);
    }

    task_runner_->PostTask(FROM_HERE, callback);
  }

  void EGLContentVideoDecoder::Reset(const base::Closure& closure) {
    resetting_ = true;
    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&EGLContentVideoDecoder::ResetTask, this, closure));
  }

  bool EGLContentVideoDecoder::NeedsBitstreamConversion() const {
    return delegate_->NeedsBitstreamConversion();
  }

  bool EGLContentVideoDecoder::CanReadWithoutStalling() const {
    return delegate_->CanDecodeNewFrame();
  }

  int EGLContentVideoDecoder::GetMaxDecodeRequests() const {
    return delegate_->GetMaxDecodeRequests();
  }

  void EGLContentVideoDecoder::InitializeTask(const InitCB& init_cb) {
    EGLContent::VideoDecoderConfig translated_config(config_);
    surface_manager.Initialise(
      config_, delegate_->GetMaxSurfaceCount(), command_buffer_stub_);
    init_cb.Run(delegate_->Initialise(translated_config));
  }

  void EGLContentVideoDecoder::DecryptTask(const scoped_refptr<DecoderBuffer>& buffer,
					   const DecodeCB& decode_cb) {
    if (pending_decrypt_)
      pending_decrypt_.Reset();

    if (!has_key_) {
      pending_decrypt_ =
	base::Bind(&EGLContentVideoDecoder::DecryptTask, this, buffer, decode_cb);
      return;
    }

    decryptor_->Decrypt(
      Decryptor::kVideo, buffer,
      base::Bind(&EGLContentVideoDecoder::OnBufferDecrypted, this, decode_cb));
  }

  void EGLContentVideoDecoder::DecodeTask(
    const scoped_refptr<DecoderBuffer>& buffer, const DecodeCB& decode_cb) {
    if (buffer->end_of_stream()) {
      delegate_->OnEndOfStream();
      decode_cb.Run(DecodeStatus::OK);
      return;
    }

    EGLContentVideoSurface* surface = surface_manager.GetSurface();

    if (!surface) {
      decode_cb.Run(DecodeStatus::DECODE_ERROR);
      return;
    }

    if (!delegate_->DecodeBuffer(buffer->data(), buffer->data_size(),
				 surface->GetEGLClientBuffer())) {
      decode_cb.Run(DecodeStatus::DECODE_ERROR);
      return;
    }

    gpu::MailboxHolder mailbox_holder[VideoFrame::kMaxPlanes] = {
      gpu::MailboxHolder(surface->Mailbox(), gpu::SyncToken(), GL_TEXTURE_2D)
    };

    output_cb_.Run(
      media::VideoFrame::WrapNativeTextures(
	media::VideoPixelFormat::PIXEL_FORMAT_ARGB, mailbox_holder,
	base::Bind(&EGLContentSurfaceManager::ReturnSurface,
		   base::Unretained(&surface_manager), surface->Id()),
        surface->CodedSize(), surface->VisibleRect(), surface->NaturalSize(),
        input_buffer->timestamp()));

    decode_cb.Run(DecodeStatus::OK);
  }

  void EGLContentVideoDecoder::ResetTask(const base::Closure& closure) {
    delegate_->Reset();
    resetting_ = false;
    closure.Run();
  }

  void EGLContentVideoDecoder::OnBufferDecrypted(
    Decryptor::Status status,
    const scoped_refptr<DecoderBuffer>& buffer,
    const DecodeCB& decode_cb) {
    if (status != Decryptor::kSuccess) {
      decode_cb.Run(DecodeStatus::DECODE_ERROR);
      return;
    }

    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(EGLContentVideoDecoder::DecodeTask, this, buffer, decode_cb));
  }

  void EGLContentVideoDecoder::OnDecryptionKeyAdded() {
    has_key_ = true;

    if (pending_decrypt_)
      task_runner_->PostTask(FROM_HERE, pending_decrypt_);
  }

}
