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

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/ptr_util.h"
#include "ui/ozone/public/ozone_platform.h"
#include "ui/ozone/public/overlay_manager_ozone.h"
#include "ui/ozone/public/cursor_factory_ozone.h"
#include "ui/ozone/public/input_controller.h"
#include "ui/ozone/public/gpu_platform_support_host.h"
#include "ui/ozone/public/system_input_injector.h"
#include "ui/ozone/common/stub_overlay_manager.h"
#include "ui/ozone/common/native_display_delegate_ozone.h"
#include "ui/events/ozone/device/device_manager.h"
#include "ui/events/ozone/layout/keyboard_layout_engine_manager.h"
#include "ui/events/ozone/layout/stub/stub_keyboard_layout_engine.h"
#include "ui/events/ozone/evdev/event_factory_evdev.h"
#include "ui/display/fake_display_delegate.h"

#include "ui/ozone/platform/eglcontent/ozone_platform_eglcontent.h"
#include "ui/ozone/platform/eglcontent/window_manager.h"
#include "ui/ozone/platform/eglcontent/cursor.h"
#include "ui/ozone/platform/eglcontent/gpu_platform_support_host.h"
#include "ui/ozone/platform/eglcontent/eglcontent_interface.h"
#include "ui/ozone/platform/eglcontent/gpu/surface_factory.h"
#include "ui/ozone/platform/eglcontent/gpu/window.h"
#include "ui/ozone/platform/eglcontent/gpu/message_filter.h"

#include "ui/views/widget/desktop_aura/desktop_factory_ozone.h"
#include "ui/views/widget/desktop_aura/desktop_window_tree_host.h"

#include "content/eglcontent/api/display_delegate.h"

#include <iostream>

namespace ui {

  namespace {

    class EGLContentOzonePlatform : public OzonePlatform {
      public :
        EGLContentOzonePlatform(EGLContent::DisplayDelegate* delegate)
          : display_delegate_(delegate) {
        }

        ~EGLContentOzonePlatform() {
        }

        SurfaceFactoryOzone* GetSurfaceFactoryOzone() override {
          return surface_factory_.get();
        }

        OverlayManagerOzone* GetOverlayManager() override {
          return overlay_manager_.get();
        }

        CursorFactoryOzone* GetCursorFactoryOzone() override {
          return cursor_factory_.get();
        }

        InputController* GetInputController() override {
          return event_factory_->input_controller();
        }

	IPC::MessageFilter* GetGpuMessageFilter() override {
	  return gpu_message_filter_.get();
	}

        GpuPlatformSupportHost* GetGpuPlatformSupportHost() override {
          return gpu_platform_support_host_.get();
        }

        std::unique_ptr<SystemInputInjector> CreateSystemInputInjector() override {
          return event_factory_->CreateSystemInputInjector();
        }

        std::unique_ptr<PlatformWindow> CreatePlatformWindow(
	  PlatformWindowDelegate* window_delegate, const gfx::Rect& bounds) override {
          return base::WrapUnique<PlatformWindow>(
	    window_manager_->CreateWindow(window_delegate, bounds));
        }

        std::unique_ptr<NativeDisplayDelegate> CreateNativeDisplayDelegate() override {
          return base::MakeUnique<display::FakeDisplayDelegate>();
        }

        void InitializeUI() override {
	  gpu_platform_support_host_.reset(new EGLContentGPUPlatformSupportHost());
	  window_manager_.reset(
	    new EGLContentWindowManager(gpu_platform_support_host_.get()));
          device_manager_ = CreateDeviceManager();
          KeyboardLayoutEngineManager::SetKeyboardLayoutEngine(
	    base::MakeUnique<StubKeyboardLayoutEngine>());
	  overlay_manager_.reset(new StubOverlayManager());
          cursor_factory_.reset(new CursorFactoryOzone());
	  cursor_.reset(new EGLContentCursor(gfx::Size(1280, 720)));
          event_factory_.reset(
            new EventFactoryEvdev(
              cursor_.get(), device_manager_.get(),
              KeyboardLayoutEngineManager::GetKeyboardLayoutEngine()));
	}

        void InitializeGPU() override {
	  gpu_message_filter_.reset(
	    new EGLContentGPUMessageFilter(display_delegate_));
	  surface_factory_.reset(
	    new EGLContentSurfaceFactory(gpu_message_filter_.get()));
        }

      private :

	// GPU Process
	std::unique_ptr<EGLContentGPUMessageFilter> gpu_message_filter_;
	std::unique_ptr<EGLContentSurfaceFactory> surface_factory_;

	// Browser Process
	std::unique_ptr<EGLContentWindowManager> window_manager_;
        std::unique_ptr<DeviceManager> device_manager_;
        std::unique_ptr<CursorFactoryOzone> cursor_factory_;
	std::unique_ptr<EGLContentCursor> cursor_;
        std::unique_ptr<EventFactoryEvdev> event_factory_;
        std::unique_ptr<OverlayManagerOzone> overlay_manager_;
        std::unique_ptr<EGLContentGPUPlatformSupportHost> gpu_platform_support_host_;

        EGLContent::DisplayDelegate* display_delegate_;

        DISALLOW_COPY_AND_ASSIGN(EGLContentOzonePlatform);
    };

  }

  OzonePlatform* CreateOzonePlatformEglcontent() {
    return new EGLContentOzonePlatform(EGLContentInterface::GetDisplayDelegate());
  }

}  // namespace ui
