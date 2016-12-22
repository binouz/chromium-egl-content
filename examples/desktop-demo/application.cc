#include "application.h"
#include "display_delegate.h"
#include "browser_delegate.h"
#include "main_delegate.h"

DemoApp::DemoApp() {
  config_.cache_path = "/tmp/eglcontent-cache";
  config_.download_directory = "/tmp/eglcontent-download";
  config_.download_name = "eglcontent";
  config_.locale = "en-us";
  config_.product_name = "eglcontent";
  config_.user_agent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.59 Safari/537.36";
  config_.accept_language;
  config_.screen_width = 1280;
  config_.screen_height = 720;
  config_.scale_factor = 1.0;
}

DemoApp::~DemoApp() {
}

EGLContent::DisplayDelegate *DemoApp::CreateDisplayDelegate() {
  return new DemoDisplayDelegate(1280, 720);
}

EGLContent::MainDelegate *DemoApp::CreateMainDelegate() {
  return new DemoMainDelegate();
}

EGLContent::BrowserDelegate *DemoApp::CreateBrowserDelegate() {
  return new DemoBrowserDelegate();
}

EGLContent::BrowserConfig& DemoApp::GetBrowserConfig() {
  return config_;
}
