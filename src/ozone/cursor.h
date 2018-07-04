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
