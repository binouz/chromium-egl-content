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

#include "ui/aura/window.h"

#include "content/public/browser/browser_thread.h"
#include "content/public/browser/navigation_controller.h"

#include "content/public/browser/render_widget_host_view.h"

#include "content/eglcontent/browser/browser.h"
#include "content/eglcontent/browser/browser_context.h"
#include "content/eglcontent/browser/aura_screen.h"

#include "content/eglcontent/api/application.h"
#include "content/eglcontent/api/browser_config.h"


namespace content {

  std::unique_ptr<EGLContentBrowser> EGLContentBrowser::g_browser;

  void EGLContentBrowser::Initialise(EGLContent::BrowserConfig& config,
				     EGLContent::BrowserDelegate* delegate) {
    g_browser.reset(new EGLContentBrowser(delegate));
    g_browser->CreateBrowserContext(config);
    g_browser->CreateWindow(config);
    g_browser->Ready();
  }

  void EGLContentBrowser::Release() {
    display::Screen::SetScreenInstance(NULL);
    g_browser.reset();
  }

  EGLContentBrowser::EGLContentBrowser(EGLContent::BrowserDelegate* delegate)
    : delegate_(delegate) {
  }

  EGLContentBrowser::~EGLContentBrowser() {;
  }

  void EGLContentBrowser::CreateBrowserContext(EGLContent::BrowserConfig& config) {
    browser_context_.reset(new EGLContentBrowserContext(config));
    browser_context_->Initialise();
  }

  void EGLContentBrowser::CreateWindow(EGLContent::BrowserConfig& config) {
    gfx::Size window_size = gfx::Size(config.screen_width, config.screen_height);
    screen_.reset(
      new EGLContentAuraScreen(window_size, config.scale_factor));
    display::Screen::SetScreenInstance(screen_.get());
    screen_->Initialise();

    WebContents::CreateParams create_params(browser_context_.get());
    create_params.initial_size = window_size;
    create_params.initially_hidden = false;
    web_contents_.reset(
      WebContents::Create(create_params));

    screen_->host()->SetBounds(gfx::Rect(window_size));
    screen_->host()->Show();

    web_contents_->SetDelegate(this);

    aura::Window* window = web_contents_->GetNativeView();
    aura::Window* parent = screen_->host()->window();

    if (!parent->Contains(window))
      parent->AddChild(window);

    window->Show();

    RenderWidgetHostView* host_view = web_contents_->GetRenderWidgetHostView();
    if (host_view)
      host_view->SetSize(window_size);
  }

  void EGLContentBrowser::Ready() {
    if (delegate_)
      delegate_->BrowserCreated(this);
  }

  void EGLContentBrowser::LoadingStateChanged(WebContents* source, bool to_different_document) {
    if (delegate_)
      delegate_->LoadingStateChanged(source->IsLoading());
  }

  void EGLContentBrowser::LoadProgressChanged(WebContents* source, double progress) {
    if (delegate_)
      delegate_->LoadProgressed(progress);
  }

  void EGLContentBrowser::UpdateTargetURL(WebContents* source, const GURL& url) {
    std::string str = url.spec();
    if (delegate_)
      delegate_->TargetURLChanged(str);
  }

  void EGLContentBrowser::LoadURL(std::string& url) {
    GURL gurl(url);
    NavigationController::LoadURLParams params(gurl);
    params.transition_type = ui::PageTransitionFromInt(
      ui::PAGE_TRANSITION_TYPED | ui::PAGE_TRANSITION_FROM_ADDRESS_BAR);
    web_contents_->GetController().LoadURLWithParams(params);
    web_contents_->Focus();
  }

  std::string EGLContentBrowser::GetURL() {
    return web_contents_->GetVisibleURL().spec();
  }

  void EGLContentBrowser::Stop() {
    web_contents_->Stop();
  }

  bool EGLContentBrowser::IsLoading() {
    return web_contents_->IsLoading();
  }

  bool EGLContentBrowser::IsAudioMuted() {
    return web_contents_->IsAudioMuted();
  }

  void EGLContentBrowser::SetAudioMuted(bool mute) {
    web_contents_->SetAudioMuted(mute);
  }

  bool EGLContentBrowser::IsCrashed() const {
    return web_contents_->IsCrashed();
  }

  void EGLContentBrowser::Reload() {
    web_contents_->GetController().Reload(false);
  }

}
