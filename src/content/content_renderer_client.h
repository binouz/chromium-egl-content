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
