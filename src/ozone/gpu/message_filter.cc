#include "ipc/ipc_message_macros.h"

#include "ui/ozone/platform/eglcontent/gpu/gpu_messages.h"
#include "ui/ozone/platform/eglcontent/gpu/display.h"
#include "ui/ozone/platform/eglcontent/gpu/window.h"
#include "ui/ozone/platform/eglcontent/gpu/message_filter.h"

namespace ui {

  EGLContentGPUMessageFilter::EGLContentGPUMessageFilter(
    EGLContent::DisplayDelegate* delegate)
    : delegate_(delegate),
      channel_(NULL) {
    display_.reset(new EGLContentDisplay(delegate_));
  }

  EGLContentGPUMessageFilter::~EGLContentGPUMessageFilter() {
  }

  void EGLContentGPUMessageFilter::OnFilterAdded(IPC::Channel* channel) {
    channel_ = channel;
  }

  void EGLContentGPUMessageFilter::OnFilterRemoved() {
    channel_ = NULL;
  }

  void EGLContentGPUMessageFilter::OnChannelConnected(int32_t peer_pid) {
  }

  void EGLContentGPUMessageFilter::OnChannelError() {
  }

  void EGLContentGPUMessageFilter::OnChannelClosing() {
  }

  bool EGLContentGPUMessageFilter::OnMessageReceived(const IPC::Message& message) {
    bool handled = true;

    IPC_BEGIN_MESSAGE_MAP(EGLContentGPUMessageFilter, message)
      IPC_MESSAGE_HANDLER(EGLContentMsg_CreateDisplay,
			  OnCreateDisplay)
      IPC_MESSAGE_HANDLER(EGLContentMsg_ReleaseDisplay,
			  OnReleaseDisplay)
      IPC_MESSAGE_HANDLER(EGLContentMsg_CreateWindow,
			  OnCreateWindow)
      IPC_MESSAGE_HANDLER(EGLContentMsg_ReleaseWindow,
			  OnReleaseWindow)
      IPC_MESSAGE_UNHANDLED(handled = false)
    IPC_END_MESSAGE_MAP()

    return handled;
  }

  void EGLContentGPUMessageFilter::OnCreateDisplay() {
  }

  void EGLContentGPUMessageFilter::OnReleaseDisplay() {
  }

  void EGLContentGPUMessageFilter::OnCreateWindow(int32_t id) {
    base::AutoLock auto_lock(lock_);
    windows_[id].reset(new EGLContentWindow(delegate_));
  }

  void EGLContentGPUMessageFilter::OnReleaseWindow(int32_t id) {
    base::AutoLock auto_lock(lock_);
    if (windows_.find(id) != windows_.end())
      windows_[id].reset();
  }

  EGLNativeDisplayType EGLContentGPUMessageFilter::GetNativeDisplay() {
    base::AutoLock auto_lock(lock_);
    return display_->GetNativeDisplay();
  }

  EGLContentWindow* EGLContentGPUMessageFilter::GetWindow(int32_t id) {
    base::AutoLock auto_lock(lock_);
    return windows_[id].get();
  }

  EGLContent::DisplayDelegate* EGLContentGPUMessageFilter::GetDisplayDelegate() {
    return delegate_;
  }
}
