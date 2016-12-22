#ifndef EGLCONTENT_API_DISPLAY_DELEGATE_H_
# define EGLCONTENT_API_DISPLAY_DELEGATE_H_

#include "third_party/khronos/EGL/egl.h"

namespace EGLContent {

  class DisplayDelegate {

    public:

      virtual EGLNativeDisplayType CreateNativeDisplay() = 0;
      virtual void ReleaseNativeDisplay() = 0;

      virtual EGLNativeWindowType CreateNativeWindow() = 0;
      virtual void ReleaseNativeWindow() = 0;

      virtual bool Resize(int size, int height, float scale_factor) = 0;

      virtual void GetSize(int* width, int* height) = 0;

      virtual char* EGLLibraryName() = 0;
      virtual char* GLESLibraryName() = 0;
  };

}

#endif // EGLCONTENT_API_DISPLAY_DELEGATE_H_
