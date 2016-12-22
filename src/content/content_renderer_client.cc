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
