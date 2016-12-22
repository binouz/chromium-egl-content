#ifndef UI_OZONE_PLATFORM_EGLCONTENT_GPU_GPU_PLATFORM_SUPPORT_HOST_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_GPU_GPU_PLATFORM_SUPPORT_HOST_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"

#include "ui/ozone/public/gpu_platform_support_host.h"

namespace ui {

  class EGLContentGPUPlatformSupportHost :
      public GpuPlatformSupportHost {

    public:

      EGLContentGPUPlatformSupportHost();
      ~EGLContentGPUPlatformSupportHost();

      // GpuPlatformSupportHost
      void OnGpuProcessLaunched(
	int host_id,
	scoped_refptr<base::SingleThreadTaskRunner> send_runner,
	const base::Callback<void(IPC::Message*)>& sender) override;
      void OnChannelEstablished() override;
      void OnChannelDestroyed(int host_id) override;

      // IPC::Listener
      bool OnMessageReceived(const IPC::Message& message) override;

      // Custom
      void CreateWindow(int32_t id);
      void ReleaseWindow(int32_t id);

    private:

      void CreateWindowOnSenderThread(int32_t id);
      void ReleaseWindowOnSenderThread(int32_t id);

      int host_id_;
      bool channel_established_;

      scoped_refptr<base::SingleThreadTaskRunner> send_runner_;
      base::Callback<void(IPC::Message*)> send_callback_;

      std::vector<int32_t> pending_window_creations_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentGPUPlatformSupportHost);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_GPU_PLATFORM_SUPPORT_HOST.H */
