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

#ifndef UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_
#define UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_

namespace ui {

  class OzonePlatform;

  // Constructor hook for use in ozone_platform_list.cc
  OzonePlatform* CreateOzonePlatformEglcontent();

}  // namespace ui

#endif  // UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_
