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

#ifndef EGLCONTENT_RENDERER_BROWSER_HOST_H_
# define EGLCONTENT_RENDERER_BROWSER_HOST_H_

#include "content/public/renderer/render_view.h"
#include "content/public/renderer/render_view_observer.h"

#include "content/eglcontent/api/browser_host.h"

namespace content {

  class EGLContentBrowserHost: public RenderViewObserver,
			       public EGLContent::BrowserHost {

    public :
      EGLContentBrowserHost(RenderView* render_view);
      ~EGLContentBrowserHost();

      void OnDestruct() override;

      void LoadURL(std::string url) override;

    private:

      RenderView* render_view_;
  };

}


#endif /* !EGLCONTENT_RENDERER_BROWSER_HOST.H */
