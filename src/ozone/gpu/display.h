#ifndef UI_OZONE_PLATFORM_EGLCONTENT_GPU_DISPLAY_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_GPU_DISPLAY_H_

#include "base/macros.h"

#include "ui/gfx/geometry/size.h"

#include "ui/gl/gl_gl_api_implementation.h"
#include "ui/gl/gl_egl_api_implementation.h"

namespace EGLContent {
  class DisplayDelegate;
}

namespace ui {

  class EGLContentDisplay {
    public:

      EGLContentDisplay(EGLContent::DisplayDelegate* delegate);
      ~EGLContentDisplay();

      gfx::Size GetSize();

      EGLNativeDisplayType GetNativeDisplay();
      EGLContent::DisplayDelegate* GetDisplayDelegate();

    private:

      gfx::Size size_;
      EGLNativeDisplayType native_display_;
      EGLContent::DisplayDelegate* delegate_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentDisplay);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_DISPLAY.H */
