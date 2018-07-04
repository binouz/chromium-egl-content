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

#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/render_view.h"

#include "content/eglcontent/api/main_delegate.h"
#include "content/eglcontent/renderer/browser_host.h"
#include "content/eglcontent/content/content_renderer_client.h"

namespace content {

  EGLContentRendererClient::EGLContentRendererClient(EGLContent::MainDelegate* delegate)
    : delegate_(delegate) {
  }

  EGLContentRendererClient::~EGLContentRendererClient() {
  }

  void EGLContentRendererClient::RenderThreadStarted() {
    LOG(INFO) << "EGLContentMainDelegate::RenderThreadStarted";
  }

  void EGLContentRendererClient::RenderFrameCreated(RenderFrame* render_frame) {
    LOG(INFO) << "EGLContentMainDelegate::RenderFrameCreated";
  }

  void EGLContentRendererClient::RenderViewCreated(RenderView* render_view) {
    LOG(INFO) << "EGLContentMainDelegate::RenderViewCreated";
  }

  void EGLContentRendererClient::CreateBrowser(RenderView* render_view, RenderFrame* render_frame) {
    if (!render_view || !render_frame || browser_host_.get())
      return;
  }

}
