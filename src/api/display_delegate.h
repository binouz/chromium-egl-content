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
