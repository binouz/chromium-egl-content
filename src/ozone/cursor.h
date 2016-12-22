#ifndef UI_OZONE_PLATFORM_EGLCONTENT_CURSOR_H_
# define UI_OZONE_PLATFORM_EGLCONTENT_CURSOR_H_

#include "base/macros.h"

#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/rect.h"

#include "ui/events/ozone/evdev/cursor_delegate_evdev.h"

namespace ui {

  class EGLContentCursor : public CursorDelegateEvdev {

    public:

      EGLContentCursor(gfx::Size display_size);
      ~EGLContentCursor() override;

      // CursorDelegateEvdev
      void MoveCursor(const gfx::Vector2dF& delta) override;
      void MoveCursorTo(gfx::AcceleratedWidget widget,
			const gfx::PointF& location) override;
      void MoveCursorTo(const gfx::PointF& location) override;
      gfx::PointF GetLocation() override;
      bool IsCursorVisible() override;
      gfx::Rect GetCursorConfinedBounds() override;
      void InitializeOnEvdev() override;

    private:

      gfx::PointF location_;
      gfx::Rect bounds_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentCursor);
  };

}

#endif /* !UI_OZONE_PLATFORM_EGLCONTENT_CURSOR.H */
