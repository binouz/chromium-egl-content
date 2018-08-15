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

#ifndef EGLCONTENT_MEDIA_AUDIO_DECODER_H_
# define EGLCONTENT_MEDIA_AUDIO_DECODER_H_

#include "media/base/audio_decoder.h"

namespace media {

  class EGLContentAudioDecoder : public AudioDecoder {

    public:

      EGLContentAudioDecoder(
	EGLContent::AudioDecoderDelegate* delegate,
	scoped_refptr<base::SingleThreadTaskRunner>& task_runner);
      ~EGLContentAudioDecoder() override;

      std::string GetDisplayName() const override;

      // Initializes an AudioDecoder with |config|, executing the |init_cb| upon
      // completion.
      //
      // |cdm_context| can be used to handle encrypted buffers. May be null if the
      // stream is not encrypted.
      // |init_cb| is used to return initialization status.
      // |output_cb| is called for decoded audio buffers (see Decode()).
      void Initialize(const AudioDecoderConfig& config,
		      CdmContext* cdm_context,
		      const InitCB& init_cb,
		      const OutputCB& output_cb) override;

      // Requests samples to be decoded. Only one decode may be in flight at any
      // given time. Once the buffer is decoded the decoder calls |decode_cb|.
      // |output_cb| specified in Initialize() is called for each decoded buffer,
      // before or after |decode_cb|.
      //
      // Implementations guarantee that the callbacks will not be called from within
      // this method.
      //
      // If |buffer| is an EOS buffer then the decoder must be flushed, i.e.
      // |output_cb| must be called for each frame pending in the queue and
      // |decode_cb| must be called after that.
      void Decode(const scoped_refptr<DecoderBuffer>& buffer,
		  const DecodeCB& decode_cb) override;

      // Resets decoder state. All pending Decode() requests will be finished or
      // aborted before |closure| is called.
      void Reset(const base::Closure& closure) override;

      // Returns true if the decoder needs bitstream conversion before decoding.
      bool NeedsBitstreamConversion() const override;

    private:

      void InitializeTask(const InitCB& init_cb);
      void DecryptTask(const scoped_refptr<DecoderBuffer>& buffer,
		       const DecodeCB& decode_cb);
      void DecodeTask(const scoped_refptr<DecoderBuffer>& input_buffer,
		      const DecodeCB& decode_cb);
      void ResetTask(const base::Closure& closure);
      void OnBufferDecrypted(Decryptor::Status status,
			     const scoped_refptr<DecoderBuffer>& buffer,
			     const DecodeCB& decode_cb);
      void OnDecryptionKeyAdded();

      EGLContent::AudioDecoderDelegate* delegate_;
      scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
      AudioDecoderConfig config_;
      Decryptor* decryptor_;
      OutputCB output_cb_;
      std::atomic<bool> has_key_;
      std::atomic<bool> resetting_;
      base::Closure pending_decode_;

  };

}

#endif /* !EGLCONTENT_MEDIA_AUDIO_DECODER.H */
