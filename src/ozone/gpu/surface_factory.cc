#include "ui/ozone/platform/eglcontent/gpu/surface_factory.h"

#include "ui/gl/egl_util.h"
#include "ui/gl/gl_surface_egl.h"

#include "ui/ozone/common/egl_util.h"
#include "ui/ozone/common/gl_ozone_egl.h"

#include "ui/ozone/platform/eglcontent/gpu/message_filter.h"
#include "ui/ozone/platform/eglcontent/gpu/window.h"

#include "content/eglcontent/api/display_delegate.h"

namespace ui {

  namespace {

    class EGLContentGLOzoneEGL : public GLOzoneEGL {
      public:

	EGLContentGLOzoneEGL(EGLContentGPUMessageFilter* message_filter)
	  : message_filter_(message_filter) {
	}

	~EGLContentGLOzoneEGL() override {
	}

	bool InitializeGLOneOffPlatform() override {
	  return GLOzoneEGL::InitializeGLOneOffPlatform();
	}

	scoped_refptr<gl::GLSurface> CreateViewGLSurface(
	  gfx::AcceleratedWidget widget) override {
	  EGLContentWindow* window = message_filter_->GetWindow(widget);

	  return gl::InitializeGLSurface(
	    new gl::NativeViewGLSurfaceEGL(window->GetNativeWindow()));
	}

	scoped_refptr<gl::GLSurface> CreateOffscreenGLSurface(
	  const gfx::Size& size) override {
	  return gl::InitializeGLSurface(new gl::PbufferGLSurfaceEGL(size));
	}

      protected:
	intptr_t GetNativeDisplay() override {
	  return reinterpret_cast<intptr_t>(
	    message_filter_->GetNativeDisplay());
	}

	bool LoadGLES2Bindings() override {
	  return LoadEGLGLES2Bindings(
	    message_filter_->GetDisplayDelegate()->EGLLibraryName(),
	    message_filter_->GetDisplayDelegate()->GLESLibraryName());
	}

      private:

	EGLContent::DisplayDelegate *delegate_;
	EGLContentGPUMessageFilter* message_filter_;

	DISALLOW_COPY_AND_ASSIGN(EGLContentGLOzoneEGL);
    };

  }

  EGLContentSurfaceFactory::EGLContentSurfaceFactory(
    EGLContentGPUMessageFilter* message_filter) {
    implementation_.reset(new EGLContentGLOzoneEGL(message_filter));
  }

  EGLContentSurfaceFactory::~EGLContentSurfaceFactory() {
  }

  std::vector<gl::GLImplementation>
  EGLContentSurfaceFactory::GetAllowedGLImplementations() {
    std::vector<gl::GLImplementation> impls;
    impls.push_back(gl::kGLImplementationEGLGLES2);
    impls.push_back(gl::kGLImplementationOSMesaGL);
    return impls;
  }

  GLOzone* EGLContentSurfaceFactory::GetGLOzone(gl::GLImplementation implementation) {
    if (implementation == gl::kGLImplementationEGLGLES2)
      return implementation_.get();

    return NULL;
  }

}
