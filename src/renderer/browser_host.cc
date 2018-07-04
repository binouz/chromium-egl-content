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
