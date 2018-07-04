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

#ifndef EGLCONTENT_BROWSER_AURA_SCREEN_H_
# define EGLCONTENT_BROWSER_AURA_SCREEN_H_

#include "ui/gfx/geometry/size.h"
#include "ui/display/screen.h"
#include "ui/display/display.h"
#include "ui/aura/window_observer.h"
#include "ui/aura/window_tree_host.h"
#include "ui/aura/client/window_tree_client.h"
#include "ui/aura/client/focus_client.h"

namespace content {

  class EGLContentAuraScreen : public display::Screen,
			       public aura::WindowObserver,
			       public aura::client::WindowTreeClient {
    public:

      EGLContentAuraScreen(gfx::Size size, float scale_factor);
      ~EGLContentAuraScreen();

      void Initialise();

      aura::WindowTreeHost* host();

      // aura::client::WindowTreeClient
      aura::Window* GetDefaultParent(aura::Window* context,
				     aura::Window* window,
				     const gfx::Rect& bounds) override;

      // display::Screen overrides
      display::Display GetPrimaryDisplay() const override;

    protected:

      // aura::WindowObserver overrides
      void OnWindowBoundsChanged(aura::Window* window,
				 const gfx::Rect& old_bounds,
				 const gfx::Rect& new_bounds) override;
      void OnWindowDestroying(aura::Window* window) override;

      // display::Screen overrides
      gfx::Point GetCursorScreenPoint() override;
      bool IsWindowUnderCursor(gfx::NativeWindow window) override;
      gfx::NativeWindow GetWindowAtScreenPoint(const gfx::Point& point) override;
      int GetNumDisplays() const override;
      std::vector<display::Display> GetAllDisplays() const override;
      display::Display GetDisplayNearestWindow(gfx::NativeView view) const override;
      display::Display GetDisplayNearestPoint(
	const gfx::Point& point) const override;
      display::Display GetDisplayMatching(
	const gfx::Rect& match_rect) const override;
      void AddObserver(display::DisplayObserver* observer) override;
      void RemoveObserver(display::DisplayObserver* observer) override;

    private:

      display::Display display_;

      std::unique_ptr<aura::WindowTreeHost> host_;
      std::unique_ptr<aura::client::FocusClient> focus_client_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentAuraScreen);
  };

}

#endif /* !EGLCONTENT_BROWSER_AURA_SCREEN.H */
