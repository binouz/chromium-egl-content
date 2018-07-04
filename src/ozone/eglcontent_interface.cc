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
