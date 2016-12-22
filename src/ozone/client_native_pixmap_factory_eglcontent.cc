#include "ui/ozone/common/stub_client_native_pixmap_factory.h"

#include "ui/ozone/platform/eglcontent/client_native_pixmap_factory_eglcontent.h"

namespace ui {

  ClientNativePixmapFactory* CreateClientNativePixmapFactoryEglcontent() {
    return CreateStubClientNativePixmapFactory();
  }

}
