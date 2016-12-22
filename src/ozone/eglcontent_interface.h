#ifndef UI_OZONE_PLATFORM_EGLCONTENT_DISPLAY_INTERFACE_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_DISPLAY_INTERFACE_H_

#include <memory>

namespace EGLContent {
  class DisplayDelegate;
}

namespace ui {

  class EGLContentInterface {

    public:
      ~EGLContentInterface();

      static EGLContent::DisplayDelegate* GetDisplayDelegate();
      static void SetDisplayDelegate(EGLContent::DisplayDelegate *delegate);

    private:
      EGLContentInterface();

      void _SetDisplayDelegate(EGLContent::DisplayDelegate *delegate);
      EGLContent::DisplayDelegate *_GetDisplayDelegate();
      std::unique_ptr<EGLContent::DisplayDelegate> display_delegate_;

      static EGLContentInterface *GetInstance();
      static std::unique_ptr<EGLContentInterface> instance;

  };
}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_DISPLAY_INTERFACE_H_ */
