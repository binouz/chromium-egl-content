#include "ui/ozone/platform/eglcontent/gpu/display.h"

#include "content/eglcontent/api/display_delegate.h"

namespace ui {

  EGLContentDisplay::EGLContentDisplay(EGLContent::DisplayDelegate* delegate)
    : native_display_(0),
      delegate_(delegate) {
    int width, height;

    native_display_ = delegate_->CreateNativeDisplay();

    delegate_->GetSize(&width, &height);
    size_ = gfx::Size(width, height);
  }

  EGLContentDisplay::~EGLContentDisplay() {
    if (native_display_)
      delegate_->ReleaseNativeDisplay();
  }

  gfx::Size EGLContentDisplay::GetSize() {
    return size_;
  }

  EGLNativeDisplayType EGLContentDisplay::GetNativeDisplay() {
    return native_display_;
  }

  EGLContent::DisplayDelegate* EGLContentDisplay::GetDisplayDelegate() {
    return delegate_;
  }

}
