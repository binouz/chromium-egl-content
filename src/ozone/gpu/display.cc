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
