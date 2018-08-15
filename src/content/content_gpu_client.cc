#include "content/eglcontent/content/content_gpu_client.h"

#include "content/eglcontent/media/mojo_media_client.h"

#include "content/eglcontent/api/media_delegate.h"

namespace content {

  EGLContentGPUClient::EGLContentGPUClient(EGLContent::MediaDelegate *media_delegate)
    : media_delegate_(media_delegate) {
  }

  EGLContentGPUClient::~EGLContentGPUClient() {
  }

  media::MojoMediaClient* EGLContentGPUClient::CreateMojoMediaClient(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    base::WeakPtr<media::MediaGpuChannelManager> media_gpu_channel_manager,
    media::CdmProxyFactoryCB& cdm_proxy_factory_cb) {
    if (media_delegate_)
      return new media::EGLContentMojoMediaClient(
        media_delegate_, task_runner, media_gpu_channel_manager, cdm_proxy_factory_cb);

    return NULL;
  }

}
