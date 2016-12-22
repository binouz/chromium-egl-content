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
