#include "ui/ozone/platform/eglcontent/cursor.h"

namespace ui {

  EGLContentCursor::EGLContentCursor(gfx::Size display_size) {
    bounds_.set_origin(gfx::Point(0, 0));
    bounds_.set_size(display_size);
  }

  EGLContentCursor::~EGLContentCursor() {
  }

  void EGLContentCursor::MoveCursor(const gfx::Vector2dF& delta) {
    location_ += delta;
  }

  void EGLContentCursor::MoveCursorTo(gfx::AcceleratedWidget widget,
				      const gfx::PointF& location) {
    location_ = location;
  }

  void EGLContentCursor::MoveCursorTo(const gfx::PointF& location) {
    location_ = location;
  }

  gfx::PointF EGLContentCursor::GetLocation() {
    return location_;
  }

  bool EGLContentCursor::IsCursorVisible() {
    return false;
  }

  gfx::Rect EGLContentCursor::GetCursorConfinedBounds() {
    return bounds_;
  }

  void EGLContentCursor::InitializeOnEvdev() {
  }

}
