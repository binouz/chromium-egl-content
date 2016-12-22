#include "content/eglcontent/api/browser_config.h"
#include "content/eglcontent/content/content_browser_client.h"
#include "content/eglcontent/browser/browser_main_parts.h"

namespace content {

  EGLContentBrowserClient::EGLContentBrowserClient(
    EGLContent::BrowserConfig& config,
    EGLContent::BrowserDelegate* delegate)
    : browser_config_(config),
      delegate_(delegate) {
  }

  EGLContentBrowserClient::~EGLContentBrowserClient() {
  }

  BrowserMainParts* EGLContentBrowserClient::CreateBrowserMainParts(
    const MainFunctionParams& parameters) {
    browser_main_parts_.reset(
      new EGLContentBrowserMainParts(browser_config_, delegate_));
    return browser_main_parts_.get();
  }

  std::string EGLContentBrowserClient::GetApplicationLocale() {
    return browser_config_.locale;
  }

  std::string EGLContentBrowserClient::GetAcceptLangs(BrowserContext* context) {
    return browser_config_.accept_language;
  }

  base::FilePath EGLContentBrowserClient::GetDefaultDownloadDirectory() {
    return base::FilePath(browser_config_.download_directory);
  }

  std::string EGLContentBrowserClient::GetDefaultDownloadName() {
    return browser_config_.download_name;
  }

}
