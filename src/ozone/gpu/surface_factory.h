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
