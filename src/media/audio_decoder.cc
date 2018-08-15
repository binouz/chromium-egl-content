// Copyright 2018 Aubin REBILLAT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "content/eglcontent/media/audio_decoder.h"

namespace media {

  namespace  {

    class AudioDecoderConfigImpl : EGLContent::AudioDecoderConfig {
    };

    class AudioDataBufferImpl : EGLcontent::AudioDataBuffer {
    };

  }

  EGLContentAudioDecoder::EGLContentAudioDecoder(
    EGLContent::AudioDecoderDelegate* delegate,
    scoped_refptr<base::SingleThreadTaskRunner>& task_runner)
    : delegate_(delegate),
      task_runner_(task_runner),
      decryptor_(NULL),
      has_key_(false),
      resetting_(false) {
  }

  EGLContentAudioDecoder::~EGLContentAudioDecoder() {
  }

  std::string EGLContentAudioDecoder::GetDisplayName() const {
    return "EGLContentAudioDecoder";
  }

  void EGLContentAudioDecoder::Initialize(const AudioDecoderConfig& config,
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
	Decryptor::kAudio,
	base::Bind(&EGLContentAudioDecoder::OnDecryptionKeyAdded, this));
    } else {
      decryptor_ = NULL;
    }

    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&EGLContentAudioDecoder::InitializeTask,
		 this, config, init_cb));
  }

  void EGLContentAudioDecoder::Decode(const scoped_refptr<DecoderBuffer>& buffer,
				      const DecodeCB& decode_cb) {
    if (resetting_) {
      decode_cb.Run(DecodeStatus::ABORTED);
      return;
    }

    base::Closure callback = base::Bind(
      &EGLContentAudioDecoder::DecodeTask, this, buffer, decode_cb);

    if (decryptor_) {
      callback = base::Bind(&EGLContentAudioDecoder::DecryptTask,
			    this, buffer, decode_cb);
    }

    task_runner_->PostTask(FROM_HERE, callback);
  }

  void EGLContentAudioDecoder::Reset(const base::Closure& closure) {
    resetting_ = true;
    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&EGLContentAudioDecoder::ResetTask, this, closure));
  }

  bool EGLContentAudioDecoder::NeedsBitstreamConversion() const {
    return delegate_->NeedBitstreamConversion();
  }

  void EGLContentAudioDecoder::InitializeTask(const InitCB& init_cb) {
    EGLContent::AudioDecoderConfig translated_config(config_);
    init_cb.Run(delegate_->Initialise(translated_config));
  }

  void EGLContentAudioDecoder::DecryptTask(const scoped_refptr<DecoderBuffer>& buffer,
					   const DecodeCB& decode_cb) {
    if (pending_decrypt_)
      pending_decrypt_.Reset();

    if (!has_key_) {
      pending_decrypt_ =
	base::Bind(&EGLContentAudioDecoder::DecryptTask, this, buffer, decode_cb);
      return;
    }

    decryptor_->Decrypt(
      Decryptor::kAudio, buffer,
      base::Bind(&EGLContentAudioDecoder::OnBufferDecrypted, this, decode_cb));
  }

  void EGLContentAudioDecoder::DecodeTask(
    const scoped_refptr<DecoderBuffer>& input_buffer, const DecodeCB& decode_cb) {
    if (input_buffer->end_of_stream()) {
      delegate_->OnEndOfStream();
      decode_cb.Run(DecodeStatus::OK);
      return;
    }

    EGLContent::AudioDataBuffer data_buffer;

    if (!delegate_->DecodeBuffer(
	  input_buffer->data(), input_buffer->data_size(), data_buffer)) {
      decode_cb.Run(DecodeStatus::DECODE_ERROR);
      return;
    }

    output_cb_.Run(
      AudioBuffer::CopyFrom(
	config_.sample_format(), config_.channel_layout(),
	data_buffer.ChannelCount(), data_buffer.SampleRate(),
	data_buffer.FrameCount(), data_buffer.Data(),
	input_buffer->timestamp()));

    decode_cb.Run(DecodeStatus::OK);
  }

  void EGLContentAudioDecoder::ResetTask(const base::Closure& closure) {
    delegate_->Reset();
    resetting_ = false;
    closure.Run();
  }

  void EGLContentAudioDecoder::OnBufferDecrypted(
    Decryptor::Status status,
    const scoped_refptr<DecoderBuffer>& buffer,
    const DecodeCB& decode_cb) {
    if (status != Decryptor::kSuccess) {
      decode_cb.Run(DecodeStatus::DECODE_ERROR);
      return;
    }

    task_runner_->PostTask(
      FROM_HERE,
      base::Bind(EGLContentAudioDecoder::DecodeTask, this, buffer, decode_cb));
  }

  void EGLContentAudioDecoder::OnDecryptionKeyAdded() {
    has_key_ = true;

    if (pending_decrypt_)
      task_runner_->PostTask(FROM_HERE, pending_decrypt_);
  }

}
