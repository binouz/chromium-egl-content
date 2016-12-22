#include "ui/ozone/platform/eglcontent/gpu/window.h"

#include "content/eglcontent/api/display_delegate.h"

namespace ui {

  EGLContentWindow::EGLContentWindow(EGLContent::DisplayDelegate* delegate)
    : delegate_(delegate) {
    native_window_ = delegate_->CreateNativeWindow();
  }

  EGLContentWindow::~EGLContentWindow() {
    delegate_->ReleaseNativeWindow();
  }

  EGLNativeWindowType EGLContentWindow::GetNativeWindow() {
    return native_window_;
  }

}
