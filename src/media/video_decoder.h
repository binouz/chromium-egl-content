#ifndef EGLCONTENT_MEDIA_VIDEO_DECODER_H_
# define EGLCONTENT_MEDIA_VIDEO_DECODER_H_

#include "media/base/video_decoder.h"

namespace media {

  class EGLContentVideoDecoder : public VideoDecoder {

    public:

      EGLContentVideoDecoder(
	EGLContent::VideoDecoderDelegate* delegate,
	scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
	gpu::GpuChannelManager* gpu_channel_manager);
      ~EGLContentVideoDecoder() override;

      std::string GetDisplayName() const;

      // Initializes a VideoDecoder with the given |config|, executing the
      // |init_cb| upon completion. |output_cb| is called for each output frame
      // decoded by Decode().
      //
      // If |low_delay| is true then the decoder is not allowed to queue frames,
      // except for out-of-order frames, i.e. if the next frame can be returned it
      // must be returned without waiting for Decode() to be called again.
      // Initialization should fail if |low_delay| is true and the decoder cannot
      // satisfy the requirements above.
      //
      // |cdm_context| can be used to handle encrypted buffers. May be null if the
      // stream is not encrypted.
      //
      // Note:
      // 1) The VideoDecoder will be reinitialized if it was initialized before.
      //    Upon reinitialization, all internal buffered frames will be dropped.
      // 2) This method should not be called during pending decode or reset.
      // 3) No VideoDecoder calls should be made before |init_cb| is executed.
      // 4) VideoDecoders should take care to run |output_cb| as soon as the frame
      // is ready (i.e. w/o thread trampolining) since it can strongly affect frame
      // delivery times with high-frame-rate material.  See Decode() for additional
      // notes.
      void Initialize(const VideoDecoderConfig& config,
                      bool low_delay,
                      CdmContext* cdm_context,
                      const InitCB& init_cb,
                      const OutputCB& output_cb) override;

      // Requests a |buffer| to be decoded. The status of the decoder and decoded
      // frame are returned via the provided callback. Some decoders may allow
      // decoding multiple buffers in parallel. Callers should call
      // GetMaxDecodeRequests() to get number of buffers that may be decoded in
      // parallel. Decoder must call |decode_cb| in the same order in which Decode()
      // is called.
      //
      // Implementations guarantee that the |decode_cb| will not be called from
      // within this method, and that it will be called even if Decode() is never
      // called again.
      // After decoding is finished the decoder calls |output_cb| specified in
      // Initialize() for each decoded frame. |output_cb| may be called before or
      // after |decode_cb|, including before Decode() returns.
      //
      // If |buffer| is an EOS buffer then the decoder must be flushed, i.e.
      // |output_cb| must be called for each frame pending in the queue and
      // |decode_cb| must be called after that. Callers will not call Decode()
      // again until after the flush completes.
      void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                  const DecodeCB& decode_cb) override;

      // Resets decoder state. All pending Decode() requests will be finished or
      // aborted before |closure| is called.
      // Note: No VideoDecoder calls should be made before |closure| is executed.
      void Reset(const base::Closure& closure) override;

      // Returns true if the decoder needs bitstream conversion before decoding.
      bool NeedsBitstreamConversion() const override;

      // Returns true if the decoder currently has the ability to decode and return
      // a VideoFrame. Most implementations can allocate a new VideoFrame and hence
      // this will always return true. Override and return false for decoders that
      // use a fixed set of VideoFrames for decoding.
      bool CanReadWithoutStalling() const override;

      // Returns maximum number of parallel decode requests.
      int GetMaxDecodeRequests() const override;

    private:

      EGLContent::VideoDecoderDelegate* delegate_;
      scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
      gpu::GpuCommandBufferStub* command_buffer_stub_;
      EGLContentSurfaceManager surface_manager_;
      VideoDecoderConfig config_;
      Decryptor* decryptor_;
      OutputCB output_cb_;
      std::atomic<bool> has_key_;
      std::atomic<bool> resetting_;
      base::Closure pending_decode_;

  };

}


#endif /* !EGLCONTENT_MEDIA_VIDEO_DECODER.H */
