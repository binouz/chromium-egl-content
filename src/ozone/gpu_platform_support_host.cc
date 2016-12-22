#include <iostream>

#include "ui/ozone/platform/eglcontent/gpu/gpu_messages.h"

#include "ui/ozone/platform/eglcontent/gpu_platform_support_host.h"

namespace ui {

  EGLContentGPUPlatformSupportHost::EGLContentGPUPlatformSupportHost()
    : host_id_(-1),
      channel_established_(false) {
  }

  EGLContentGPUPlatformSupportHost::~EGLContentGPUPlatformSupportHost() {
  }

  void EGLContentGPUPlatformSupportHost::OnGpuProcessLaunched(
    int host_id,
    scoped_refptr<base::SingleThreadTaskRunner> send_runner,
    const base::Callback<void(IPC::Message*)>& send_callback) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    host_id_ = host_id;
    send_runner_ = send_runner;
    send_callback_ = send_callback;
  }

  void EGLContentGPUPlatformSupportHost::OnChannelEstablished() {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    channel_established_ = true;

    if (pending_window_creations_.size() > 0) {
      for (std::vector<int32_t>::iterator it = pending_window_creations_.begin();
	   it != pending_window_creations_.end(); ++it)
	CreateWindow(*it);
    }
  }

  void EGLContentGPUPlatformSupportHost::OnChannelDestroyed(int host_id) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    if (host_id_ == host_id) {
      host_id_ = -1;
      channel_established_ = false;
      send_runner_ = nullptr;
      send_callback_.Reset();
    }
  }

  bool EGLContentGPUPlatformSupportHost::OnMessageReceived(const IPC::Message& message) {
    return false;
    // bool handled = true;

    // IPC_BEGIN_MESSAGE_MAP(EGLContentGPUPlatformSupportHost, message)
    //   // IPC_MESSAGE_HANDLER(EGLContentHostMsg_ , )
    //   IPC_MESSAGE_UNHANDLED(handled = false)
    // IPC_END_MESSAGE_MAP()

    // return handled;
  }

  void EGLContentGPUPlatformSupportHost::CreateWindow(int32_t id) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    if (!channel_established_) {
      pending_window_creations_.push_back(id);
      return;
    }
    if (send_runner_->BelongsToCurrentThread()) {
      CreateWindowOnSenderThread(id);
    } else {
      send_runner_->PostTask(
	FROM_HERE,
	base::Bind(&EGLContentGPUPlatformSupportHost::CreateWindowOnSenderThread,
		   base::Unretained(this), id));
    }
  }

  void EGLContentGPUPlatformSupportHost::ReleaseWindow(int32_t id) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    if (send_runner_->BelongsToCurrentThread()) {
      ReleaseWindowOnSenderThread(id);
    } else {
      send_runner_->PostTask(
	FROM_HERE,
	base::Bind(&EGLContentGPUPlatformSupportHost::ReleaseWindowOnSenderThread,
		   base::Unretained(this), id));
    }
  }

  void EGLContentGPUPlatformSupportHost::CreateWindowOnSenderThread(int32_t id) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    IPC::Message* message = new EGLContentMsg_CreateWindow(id);
    send_callback_.Run(message);
  }

  void EGLContentGPUPlatformSupportHost::ReleaseWindowOnSenderThread(int32_t id) {
    LOG(INFO) << "EGLContentGPUPlatformSupportHost::" << __FUNCTION__;
    IPC::Message* message = new EGLContentMsg_ReleaseWindow(id);
    send_callback_.Run(message);
  }

}