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

#ifndef DISPLAY_DELEGATE_H_
# define DISPLAY_DELEGATE_H_

#include <eglcontent/display_delegate.h>

#define X_DISPLAY_NAME "EGLContent DemoApp"

class DemoDisplayDelegate: public EGLContent::DisplayDelegate {

  public:

    DemoDisplayDelegate(int width, int height);
    ~DemoDisplayDelegate();

    EGLNativeDisplayType CreateNativeDisplay() override;
    void ReleaseNativeDisplay() override;

    EGLNativeWindowType CreateNativeWindow() override;
    void ReleaseNativeWindow() override;

    bool Resize(int size, int height, float scale_factor) override;

    void GetSize(int* width, int* height) override;

    char* EGLLibraryName() override;
    char* GLESLibraryName() override;

  private:

    int width_;
    int height_;

    Display *x_display_;
    Window x_window_;

};

#endif /* !DISPLAY_DELEGATE.H */
