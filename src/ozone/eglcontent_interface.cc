#include "ui/ozone/platform/eglcontent/eglcontent_interface.h"
#include "content/eglcontent/api/display_delegate.h"

namespace ui {

  std::unique_ptr<EGLContentInterface> EGLContentInterface::instance;

  EGLContentInterface::EGLContentInterface() {
  }

  EGLContentInterface::~EGLContentInterface() {
    instance.reset(NULL);
  }

  EGLContent::DisplayDelegate *EGLContentInterface::GetDisplayDelegate() {
    return EGLContentInterface::GetInstance()->_GetDisplayDelegate();
  }

  void EGLContentInterface::SetDisplayDelegate(EGLContent::DisplayDelegate *delegate) {
    return EGLContentInterface::GetInstance()->_SetDisplayDelegate(delegate);
  }

  EGLContentInterface *EGLContentInterface::GetInstance() {
    if (!instance.get())
      instance.reset(new EGLContentInterface());
    return instance.get();
  }

  EGLContent::DisplayDelegate *EGLContentInterface::_GetDisplayDelegate() {
    return display_delegate_.get();
  }

  void EGLContentInterface::_SetDisplayDelegate(EGLContent::DisplayDelegate *delegate) {
    return display_delegate_.reset(delegate);
  }

}
