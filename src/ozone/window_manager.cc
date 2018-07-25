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

#include "base/bind.h"

#include "ui/events/event.h"
#include "ui/events/ozone/events_ozone.h"
#include "ui/events/platform/platform_event_source.h"
#include "ui/platform_window/platform_window_delegate.h"

#include "ui/ozone/platform/eglcontent/window_manager.h"
#include "ui/ozone/platform/eglcontent/gpu_platform_support_host.h"

namespace ui {

  EGLContentPlatformWindow::EGLContentPlatformWindow()
    : manager_(NULL),
      delegate_(NULL) {
  }

  EGLContentPlatformWindow::~EGLContentPlatformWindow() {
    manager_->RemoveWindow(widget_);
  }

  void EGLContentPlatformWindow::Initialise(EGLContentWindowManager* manager,
                                            PlatformWindowDelegate* delegate,
                                            const gfx::Rect& bounds) {
    manager_ = manager;
    delegate_ = delegate;
    bounds_ = bounds;
  }

  void EGLContentPlatformWindow::SetWidget(gfx::AcceleratedWidget widget) {
    widget_ = widget;
  }

  gfx::Rect EGLContentPlatformWindow::GetBounds() {
    return bounds_;
  }

  void EGLContentPlatformWindow::SetBounds(const gfx::Rect& bounds) {
    delegate_->OnBoundsChanged(bounds_);
  }

  void EGLContentPlatformWindow::SetTitle(const base::string16& title) {
  }

  void EGLContentPlatformWindow::Show() {
  }

  void EGLContentPlatformWindow::Hide() {
  }

  void EGLContentPlatformWindow::Close() {
  }

  void EGLContentPlatformWindow::SetCapture() {
  }

  void EGLContentPlatformWindow::ReleaseCapture() {
  }

  void EGLContentPlatformWindow::ToggleFullscreen() {
  }

  void EGLContentPlatformWindow::Maximize() {
  }

  void EGLContentPlatformWindow::Minimize() {
  }

  void EGLContentPlatformWindow::Restore() {
  }

  void EGLContentPlatformWindow::SetCursor(PlatformCursor cursor) {
  }

  void EGLContentPlatformWindow::MoveCursorTo(const gfx::Point& location) {
  }

  void EGLContentPlatformWindow::ConfineCursorToBounds(const gfx::Rect& bounds) {
  }

  PlatformImeController* EGLContentPlatformWindow::GetPlatformImeController() {
    return NULL;
  }

  void EGLContentPlatformWindow::PrepareForShutdown() {
  }

  bool EGLContentPlatformWindow::HasCapture() const {
    return false;
  }

  bool EGLContentPlatformWindow::CanDispatchEvent(const PlatformEvent& event) {
    return true;
  }

  uint32_t EGLContentPlatformWindow::DispatchEvent(const PlatformEvent& native_event) {
    Event* event = static_cast<Event*>(native_event);
    if (event->IsLocatedEvent()) {
      LocatedEvent* located_event = event->AsLocatedEvent();
      gfx::PointF location = located_event->location_f()
	- gfx::Vector2dF(bounds_.OffsetFromOrigin());
      located_event->set_location_f(location);
      located_event->set_root_location_f(location);
    }
    DispatchEventFromNativeUiEvent(
      native_event, base::Bind(&PlatformWindowDelegate::DispatchEvent,
                               base::Unretained(delegate_)));
    return POST_DISPATCH_STOP_PROPAGATION;
  }

  EGLContentWindowManager::EGLContentWindowManager(
    EGLContentGPUPlatformSupportHost* gpu_platform_support)
    : gpu_platform_support_(gpu_platform_support) {
  }

  EGLContentWindowManager::~EGLContentWindowManager() {
  }

  EGLContentPlatformWindow* EGLContentWindowManager::CreateWindow(
    PlatformWindowDelegate* window_delegate, const gfx::Rect& bounds) {
    EGLContentPlatformWindow* window = new EGLContentPlatformWindow();
    gfx::AcceleratedWidget widget = windows_.Add(window);

    window->Initialise(this, window_delegate, bounds);
    window->SetWidget(widget);
    gpu_platform_support_->CreateWindow(widget);
    window_delegate->OnAcceleratedWidgetAvailable(widget, 1.f);

    return window;
  }

  void EGLContentWindowManager::RemoveWindow(gfx::AcceleratedWidget window_id) {
    if (windows_.Lookup(window_id)) {
      windows_.Remove(window_id);
      gpu_platform_support_->ReleaseWindow(window_id);
    }
  }

  EGLContentPlatformWindow* EGLContentWindowManager::GetWindow(int32_t window_id) {
    return windows_.Lookup(window_id);
  }

}
