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
    LOG(INFO) << "EGLContentBrowser::Initialise: delegate=" << (void*) delegate;
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
    LOG(INFO) << "EGLContentBrowser::" << __FUNCTION__
	      << " size.width=" << config.screen_width
	      << " size.height=" << config.screen_height;
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
    LOG(INFO) << "EGLContentBrowser::Ready";
    if (delegate_)
      delegate_->BrowserCreated(this);
  }

  void EGLContentBrowser::LoadingStateChanged(WebContents* source, bool to_different_document) {
    LOG(INFO) << "EGLContentBrowser::LoadingStateChanged: loading="
	      << (source->IsLoading() ? "TRUE" : "FALSE");
    if (delegate_)
      delegate_->LoadingStateChanged(source->IsLoading());
  }

  void EGLContentBrowser::LoadProgressChanged(WebContents* source, double progress) {
    LOG(INFO) << "EGLContentBrowser::LoadingProgressChanged: progress="
	      << progress;
    if (delegate_)
      delegate_->LoadProgressed(progress);
  }

  void EGLContentBrowser::UpdateTargetURL(WebContents* source, const GURL& url) {
    std::string scheme = url.scheme_piece().as_string();
    std::string content = url.GetContent();
    std::string str = scheme + ":" + content;
    LOG(INFO) << "EGLContentBrowser::UpdateTargetURL: url=" << str;
    if (delegate_)
      delegate_->TargetURLChanged(str);
  }

  void EGLContentBrowser::LoadURL(std::string& url) {
    LOG(INFO) << "EGLContentBrowser::LoadURL: url=" << url;
    GURL gurl(url);
    NavigationController::LoadURLParams params(gurl);
    params.transition_type = ui::PageTransitionFromInt(
      ui::PAGE_TRANSITION_TYPED | ui::PAGE_TRANSITION_FROM_ADDRESS_BAR);
    web_contents_->GetController().LoadURLWithParams(params);
    web_contents_->Focus();
  }

}