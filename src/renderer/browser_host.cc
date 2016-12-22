#include "third_party/WebKit/public/web/WebView.h"
#include "third_party/WebKit/public/web/WebFrame.h"
#include "third_party/WebKit/public/platform/WebURLRequest.h"

#include "content/eglcontent/renderer/browser_host.h"

namespace content {

  EGLContentBrowserHost::EGLContentBrowserHost(RenderView* render_view)
    : RenderViewObserver(render_view),
      render_view_(render_view) {
  }

  EGLContentBrowserHost::~EGLContentBrowserHost() {
  }

  void EGLContentBrowserHost::LoadURL(std::string url) {
    blink::WebURLRequest request = blink::WebURLRequest(GURL(url));
    render_view_->GetWebView()->mainFrame()->loadRequest(request);
  }

  void EGLContentBrowserHost::OnDestruct() {
  }

}
