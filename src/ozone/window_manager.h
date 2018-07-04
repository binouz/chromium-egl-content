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

#ifndef UI_OZONE_PLATFORM_EGLCONTENT_WINDOW_MANAGER_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_WINDOW_MANAGER_H_

#include "base/macros.h"
#include "base/id_map.h"
#include "base/synchronization/lock.h"

#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/native_widget_types.h"

#include "ui/platform_window/platform_window.h"

#include "ui/events/platform/platform_event_dispatcher.h"

namespace ui {

  class EGLContentGPUPlatformSupportHost;
  class EGLContentWindowManager;

  class EGLContentPlatformWindow : public PlatformWindow,
				   public PlatformEventDispatcher {
    public:
      EGLContentPlatformWindow(EGLContentWindowManager* manager,
			       PlatformWindowDelegate* delegate,
			       const gfx::Rect& bounds);
      ~EGLContentPlatformWindow() override;

      void SetWidget(gfx::AcceleratedWidget widget);

      // PlatformWindow
      gfx::Rect GetBounds() override;
      void SetBounds(const gfx::Rect& bounds) override;
      void SetTitle(const base::string16& title) override;
      void Show() override;
      void Hide() override;
      void Close() override;
      void SetCapture() override;
      void ReleaseCapture() override;
      void ToggleFullscreen() override;
      void Maximize() override;
      void Minimize() override;
      void Restore() override;
      void SetCursor(PlatformCursor cursor) override;
      void MoveCursorTo(const gfx::Point& location) override;
      void ConfineCursorToBounds(const gfx::Rect& bounds) override;
      PlatformImeController* GetPlatformImeController() override;

      // PlatformEventDispatcher
      bool CanDispatchEvent(const PlatformEvent& event) override;
      uint32_t DispatchEvent(const PlatformEvent& event) override;

    private:

      EGLContentWindowManager* manager_;
      PlatformWindowDelegate* delegate_;
      gfx::Rect bounds_;
      gfx::AcceleratedWidget widget_;
      DISALLOW_COPY_AND_ASSIGN(EGLContentPlatformWindow);
  };

  class EGLContentWindowManager {
    public:

      EGLContentWindowManager(EGLContentGPUPlatformSupportHost* gpu_platform_support);
      ~EGLContentWindowManager();

      EGLContentPlatformWindow* CreateWindow(
	PlatformWindowDelegate* window_delegate, const gfx::Rect& bounds);

      void RemoveWindow(gfx::AcceleratedWidget window_id);
      EGLContentPlatformWindow* GetWindow(gfx::AcceleratedWidget window_id);

    private:

      EGLContentGPUPlatformSupportHost* gpu_platform_support_;
      IDMap<EGLContentPlatformWindow> windows_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentWindowManager);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_WINDOW_MANAGER.H */
