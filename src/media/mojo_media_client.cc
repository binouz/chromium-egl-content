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

#include "base/message_loop/message_loop.h"

#include "content/eglcontent/media/mojo_media_client.h"
#include "content/eglcontent/media/audio_decoder.h"
#include "content/eglcontent/media/video_decoder.h"
#include "content/eglcontent/media/audio_renderer_sink.h"
#include "content/eglcontent/media/video_renderer_sink.h"
#include "content/eglcontent/media/renderer_factory.h"
#include "content/eglcontent/media/cdm_factory.h"

namespace media {

  EGLContentMojoMediaClient::EGLContentMojoMediaClient(
    EGLContent::MediaDelegate* delegate,
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    base::WeakPtr<media::MediaGpuChannelManager> media_gpu_channel_manager,
    media::CdmProxyFactoryCB& cdm_proxy_factory_cb)
    : delegate_(delegate),
      task_runner_(task_runner),
      media_gpu_channel_manager_(media_gpu_channel_manager),
      cdm_proxy_factory_cb_(std::move(cdm_proxy_factory_cb)) {
    delegate_->InitialiseMediaPlatform();
  }

  EGLContentMojoMediaClient::~EGLContentMojoMediaClient() {
    if (delegate_)
      delegate_->Cleanup();
  }

  std::unique_ptr<AudioDecoder> EGLContentMojoMediaClient::CreateAudioDecoder(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner) {
    return base::MakeUnique<EGLContentAudioDecoder>(
      delegate_->CreateAudioDecoderDelegate(), task_runner);
  }

  std::unique_ptr<VideoDecoder> EGLContentMojoMediaClient::CreateVideoDecoder(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    MediaLog* media_log,
    mojom::CommandBufferIdPtr command_buffer_id) {
    gpu::GpuChannel* channel =
      media_gpu_channel_manager_->LookupChannel(command_buffer_id->channel_token);

    if (!channel) {
      LOG(WARNING) << "Unable to find corresponding GPU channel";
      return NULL;
    }

    gpu::CommandBufferStub* stub = channel->LookupCommandBuffer(
      command_buffer_id->route_id);

    if (!stub) {
      LOG(WARNING) << "Unable to find corresponding GPU command buffer";
      return NULL;
    }

    return base::MakeUnique<EGLContentVideoDecoder>(
      delegate_->CreateVideoDecoderDelegate(), task_runner, stub);
  }

  scoped_refptr<AudioRendererSink> EGLContentMojoMediaClient::CreateAudioRendererSink(
    const std::string& audio_device_id) {
    EGLContent::AudioSinkDelegate* sink_delegate =
      delegate_->CreateAudioSinkDelegate();

    if (sink_delegate)
      return new EGLContentAudioRendererSink(sink_delegate);

    return new NullAudioSink(base::MessageLoop::Current()->task_runner());
  }

  std::unique_ptr<VideoRendererSink> EGLContentMojoMediaClient::CreateVideoRendererSink(
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner) {
    EGLContent::VideoSinkDelegate* sink_delegate =
      delegate_->CreateVideoSinkDelegate();

    if (sink_delegate)
      return new EGLContentVideoRendererSink(sink_delegate);

    return base::MakeUnique<NullVideoSink>(
      false, base::TimeDelta::FromSecondsD(1.0 / 60),
      NullVideoSink::NewFrameCB(), task_runner);
  }

  std::unique_ptr<RendererFactory> EGLContentMojoMediaClient::CreateRendererFactory(
    const scoped_refptr<MediaLog>& media_log) {
    return base::MakeUnique<EGLContentRendererFactory>(
      delegate_, media_log);
  }

  std::unique_ptr<CdmFactory> EGLContentMojoMediaClient::CreateCdmFactory(
    shell::mojom::InterfaceProvider* host_interfaces) {
    return base::MakeUnique<EGLContentCDMFactory>(
      delegate_, interface_provider);
  }

}
