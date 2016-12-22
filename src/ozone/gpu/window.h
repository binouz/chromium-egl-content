#ifndef UI_OZONE_PLATFORM_EGLCONTENT_GPU_WINDOW_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_GPU_WINDOW_H_

#include "base/macros.h"

#include "ui/gl/gl_gl_api_implementation.h"
#include "ui/gl/gl_egl_api_implementation.h"

namespace EGLContent {
  class DisplayDelegate;
}

namespace ui {

  class EGLContentWindow {

    public:

      EGLContentWindow(EGLContent::DisplayDelegate* delegate);
      ~EGLContentWindow();

      EGLNativeWindowType GetNativeWindow();

    private:

      EGLContent::DisplayDelegate* delegate_;

      EGLNativeWindowType native_window_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentWindow);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_WINDOW.H */
