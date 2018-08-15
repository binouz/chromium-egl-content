#ifndef EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT_H_
# define EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT_H_

#include "media/mojo/services/mojo_media_client.h"

namespace EGLContent {
  class MediaDelegate;
}

namespace media {

  class EGLContentMojoMediaClient : public MojoMediaClient {

    public:

      EGLContentMojoMediaClient(
        EGLContent::MediaDelegate* delegate,
        scoped_refptr<base::SingleThreadTaskRunner> task_runner,
        base::WeakPtr<media::MediaGpuChannelManager> media_gpu_channel_manager,
        media::CdmProxyFactoryCB& cdm_proxy_factory_cb);
      ~EGLContentMojoMediaClient() override;

      std::unique_ptr<AudioDecoder> CreateAudioDecoder(
        scoped_refptr<base::SingleThreadTaskRunner> task_runner) override;

      std::unique_ptr<VideoDecoder> CreateVideoDecoder(
        scoped_refptr<base::SingleThreadTaskRunner> task_runner,
        MediaLog* media_log,
        mojom::CommandBufferIdPtr command_buffer_id,
        RequestOverlayInfoCB request_overlay_info_cb) override;

      scoped_refptr<AudioRendererSink> CreateAudioRendererSink(
        const std::string& audio_device_id) override;

      std::unique_ptr<VideoRendererSink> CreateVideoRendererSink(
        const scoped_refptr<base::SingleThreadTaskRunner>& task_runner) override;

      std::unique_ptr<RendererFactory> CreateRendererFactory(
        MediaLog* media_log) override;

      std::unique_ptr<CdmFactory> CreateCdmFactory(
        service_manager::mojom::InterfaceProvider* host_interfaces) override;

    private:

      EGLContent::MediaDelegate* delegate_;
      scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
      base::WeakPtr<media::MediaGpuChannelManager> media_gpu_channel_manager_;
      media::CdmProxyFactoryCB cdm_proxy_factory_cb_;

  };

}

#endif /* !EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT.H */
