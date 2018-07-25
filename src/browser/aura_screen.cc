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

#include "base/scoped_observer.h"

#include "ui/base/ime/input_method.h"

#include "ui/aura/env.h"
#include "ui/aura/window.h"
#include "ui/aura/layout_manager.h"

#include "ui/aura/client/focus_change_observer.h"

#include "ui/wm/core/default_activation_client.h"

#include "content/eglcontent/browser/aura_screen.h"

namespace content {

  namespace {

    class FillLayout : public aura::LayoutManager {
      public:
	explicit FillLayout(aura::Window* root)
	  : root_(root) {
	}

	virtual ~FillLayout() {}

      private:
	// aura::LayoutManager:
	virtual void OnWindowResized() {
	}

	virtual void OnWindowAddedToLayout(aura::Window* child) {
	  child->SetBounds(root_->bounds());
	}

	virtual void OnWillRemoveWindowFromLayout(aura::Window* child) {
	}

	virtual void OnWindowRemovedFromLayout(aura::Window* child) {
	}

	virtual void OnChildWindowVisibilityChanged(aura::Window* child,
						    bool visible) {
	}

	virtual void SetChildBounds(aura::Window* child,
				    const gfx::Rect& requested_bounds) {
	  SetChildBoundsDirect(child, requested_bounds);
	}

	aura::Window* root_;

	DISALLOW_COPY_AND_ASSIGN(FillLayout);
    };

    class FocusClient : public aura::client::FocusClient,
                        public aura::WindowObserver {
      public:
	FocusClient()
	  : focused_window_(NULL),
	    observer_manager_(this) {
	}

	~FocusClient() override {
	}

      private:
	// Overridden from client::FocusClient:
	void AddObserver(aura::client::FocusChangeObserver* observer) override {
	  focus_observers_.AddObserver(observer);
	}

	void RemoveObserver(aura::client::FocusChangeObserver* observer) override {
	  focus_observers_.RemoveObserver(observer);
	}

	void FocusWindow(aura::Window* window) override {
	  if (window && !window->CanFocus())
	    return;

	  aura::Window* old_focused_window = focused_window_;

	  if (focused_window_)
	    observer_manager_.Remove(focused_window_);

	  focused_window_ = window;
	  if (focused_window_)
	    observer_manager_.Add(focused_window_);

	  for (aura::client::FocusChangeObserver& observer : focus_observers_)
            observer.OnWindowFocused(focused_window_, old_focused_window);

	  aura::client::FocusChangeObserver* observer =
	    aura::client::GetFocusChangeObserver(old_focused_window);

	  if (observer)
	    observer->OnWindowFocused(focused_window_, old_focused_window);

	  observer = aura::client::GetFocusChangeObserver(focused_window_);
	  if (observer)
	    observer->OnWindowFocused(focused_window_, old_focused_window);
	}

	void ResetFocusWithinActiveWindow(aura::Window* window) override {
	  if (!window->Contains(focused_window_))
	    FocusWindow(window);
	}

	aura::Window* GetFocusedWindow() override {
	  return focused_window_;
	}

	// Overridden from WindowObserver:
	void OnWindowDestroying(aura::Window* window) override {
	  FocusWindow(NULL);
	}

	aura::Window* focused_window_;
	ScopedObserver<aura::Window, aura::WindowObserver> observer_manager_;
	base::ObserverList<aura::client::FocusChangeObserver> focus_observers_;

	DISALLOW_COPY_AND_ASSIGN(FocusClient);
    };

  }

  EGLContentAuraScreen::EGLContentAuraScreen(gfx::Size size, float scale_factor) {
    static int64_t synthesized_display_id = 2000;
    display_.set_id(synthesized_display_id++);
    display_.SetScaleAndBounds(scale_factor, gfx::Rect(size));
    displays_vect_.push_back(display_);
  }

  EGLContentAuraScreen::~EGLContentAuraScreen() {
  }

  void EGLContentAuraScreen::Initialise() {
    host_.reset(aura::WindowTreeHost::Create(gfx::Rect(display_.GetSizeInPixel())));
    host_->InitHost();
    host_->window()->SetLayoutManager(new FillLayout(host_->window()));
    host_->window()->AddObserver(this);

    focus_client_.reset(new FocusClient());
    aura::client::SetFocusClient(host_->window(), focus_client_.get());

    new wm::DefaultActivationClient(host_->window());
  }

  aura::WindowTreeHost* EGLContentAuraScreen::host() {
    return host_.get();
  }

  display::Display EGLContentAuraScreen::GetPrimaryDisplay() const {
    return display_;
  }

  void EGLContentAuraScreen::OnWindowBoundsChanged(aura::Window* window,
                                                   const gfx::Rect& old_bounds,
                                                   const gfx::Rect& new_bounds,
                                                   ui::PropertyChangeReason reason) {
    display_.SetSize(gfx::ScaleToFlooredSize(
                       new_bounds.size(), display_.device_scale_factor()));
  }

  void EGLContentAuraScreen::OnWindowDestroying(aura::Window* window) {
    if (host_->window() == window)
      host_.reset(NULL);
  }

  gfx::Point EGLContentAuraScreen::GetCursorScreenPoint() {
    return aura::Env::GetInstance()->last_mouse_location();
  }

  bool EGLContentAuraScreen::IsWindowUnderCursor(gfx::NativeWindow window) {
    return GetWindowAtScreenPoint(GetCursorScreenPoint()) == window;
  }

  gfx::NativeWindow EGLContentAuraScreen::GetWindowAtScreenPoint(const gfx::Point& point) {
    if (!host_.get() || !host_->window())
      return NULL;
    return host_->window();
  }

  int EGLContentAuraScreen::GetNumDisplays() const {
    return displays_vect_.size();
  }

  const std::vector<display::Display>& EGLContentAuraScreen::GetAllDisplays() const {
    return displays_vect_;
  }

  display::Display EGLContentAuraScreen::GetDisplayNearestWindow(gfx::NativeView view) const {
    return display_;
  }

  display::Display EGLContentAuraScreen::GetDisplayNearestPoint(
    const gfx::Point& point) const {
    return display_;
  }

  display::Display EGLContentAuraScreen::GetDisplayMatching(
    const gfx::Rect& match_rect) const {
    return display_;
  }

  void EGLContentAuraScreen::AddObserver(display::DisplayObserver* observer) {
  }

  void EGLContentAuraScreen::RemoveObserver(display::DisplayObserver* observer) {
  }

}
