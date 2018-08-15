#ifndef EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT_H_

#include "content/public/gpu/content_gpu_client.h"

namespace EGLContent {
  class MediaDelegate;
}

namespace content {

  class EGLContentGPUClient : ContentGpuClient {
    public:

      EGLContentGPUClient(EGLContent::MediaDelegate *media_delegate);
      ~EGLContentGPUClient() override;

      media::MojoMediaClient* CreateMojoMediaClient(
        scoped_refptr<base::SingleThreadTaskRunner> task_runner,
        base::WeakPtr<media::MediaGpuChannelManager> media_gpu_channel_manager,
        media::CdmProxyFactoryCB& cdm_proxy_factory_cb) override;

    private:

      EGLContent::MediaDelegate *media_delegate_;
  };

}

#endif /* !EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT.H */
