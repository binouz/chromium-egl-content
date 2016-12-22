#ifndef UI_OZONE_PLATFORM_EGLCONTENT_GPU_SURFACE_FACTORY_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_GPU_SURFACE_FACTORY_H_

#include "base/macros.h"

#include "ui/ozone/public/surface_factory_ozone.h"

namespace ui {

  class EGLContentGPUMessageFilter;

  class EGLContentSurfaceFactory : public SurfaceFactoryOzone {

    public:

      EGLContentSurfaceFactory(EGLContentGPUMessageFilter* message_filter);
      ~EGLContentSurfaceFactory() override;

      // SurfaceFactoryOzone:
      std::vector<gl::GLImplementation> GetAllowedGLImplementations() override;
      GLOzone* GetGLOzone(gl::GLImplementation implementation) override;

    private:

      std::unique_ptr<GLOzone> implementation_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentSurfaceFactory);
  };

}  // namespace ui

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_GPU_SURFACE_FACTORY.H */
