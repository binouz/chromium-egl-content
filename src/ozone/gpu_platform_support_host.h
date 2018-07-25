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
	scoped_refptr<base::SingleThreadTaskRunner> ui_runner,
	scoped_refptr<base::SingleThreadTaskRunner> send_runner,
	const base::Callback<void(IPC::Message*)>& sender) override;
      void OnChannelDestroyed(int host_id) override;
      void OnGpuServiceLaunched(
        scoped_refptr<base::SingleThreadTaskRunner> host_runner,
        scoped_refptr<base::SingleThreadTaskRunner> io_runner,
        GpuHostBindInterfaceCallback binder) override;

      // IPC::Listener
      void OnMessageReceived(const IPC::Message& message) override;

      // Custom
      void CreateWindow(int32_t id);
      void ReleaseWindow(int32_t id);

    private:

      void CreateWindowOnSenderThread(int32_t id);
      void ReleaseWindowOnSenderThread(int32_t id);

      int host_id_;
      bool service_launched_;

      std::vector<int32_t> pending_window_creations_;

      scoped_refptr<base::SingleThreadTaskRunner> send_runner_;
      base::Callback<void(IPC::Message*)> send_callback_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentGPUPlatformSupportHost);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_GPU_PLATFORM_SUPPORT_HOST.H */
