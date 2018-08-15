#ifndef EGLCONTENT_API_AUDIO_DECODER_DELEGATE_H_
# define EGLCONTENT_API_AUDIO_DECODER_DELEGATE_H_

namespace EGLContent {

  class AudioDecoderConfig {

  };

  class AudioDataBuffer {

  };

  class AudioDecoderDelegate {

    public:

      bool NeedBitstreamConversion();
      bool Initialise(AudioDecoderConfig& config);
      bool DecodeBuffer(void *data, size_t size, AudioDataBuffer& output);
      void OnEndOfStream();
      void Reset();

  };

}

#endif /* !EGLCONTENT_API_AUDIO_DECODER_DELEGATE.H */
