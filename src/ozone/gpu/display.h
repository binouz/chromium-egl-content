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
