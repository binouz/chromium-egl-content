#ifndef UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_
#define UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_

namespace ui {

  class OzonePlatform;

  // Constructor hook for use in ozone_platform_list.cc
  OzonePlatform* CreateOzonePlatformEglcontent();

}  // namespace ui

#endif  // UI_OZONE_PLATFORM_EGLCONTENT_OZONE_PLATFORM_EGLCONTENT_H_
