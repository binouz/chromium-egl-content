#ifndef EGLCONTENT_CONTENT_CONTENT_RENDERER_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_RENDERER_CLIENT_H_

#include "content/public/renderer/content_renderer_client.h"

namespace EGLContent {
  class MainDelegate;
  struct BrowserConfig;
}

namespace content {

  class EGLContentBrowserHost;

  class EGLContentRendererClient : public ContentRendererClient {

    public:
      EGLContentRendererClient(EGLContent::MainDelegate* delegate);
      ~EGLContentRendererClient();

      // Notifies us that the RenderThread has been created.
      void RenderThreadStarted() override;

      // Notifies that a new RenderFrame has been created.
      void RenderFrameCreated(RenderFrame* render_frame) override;

      // Notifies that a new RenderView has been created.
      void RenderViewCreated(RenderView* render_view) override;

    private:

      void CreateBrowser(RenderView* render_view, RenderFrame* render_frame);

      EGLContent::MainDelegate* delegate_;

      std::unique_ptr<EGLContentBrowserHost> browser_host_;
  };

}

#endif /* !EGLCONTENT_CONTENT_CONTENT_RENDERER_CLIENT_H_ */
