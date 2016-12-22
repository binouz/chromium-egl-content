#ifndef EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_

#include "content/public/browser/content_browser_client.h"

#include "content/eglcontent/browser/browser_main_parts.h"

#include "content/eglcontent/api/main_delegate.h"

#include <memory>

namespace EGLContent {
  struct BrowserConfig;
  class BrowserDelegate;
}

namespace content {

  class EGLContentBrowserClient : public ContentBrowserClient {
    public:

      EGLContentBrowserClient(EGLContent::BrowserConfig& config,
			      EGLContent::BrowserDelegate* delegate);
      ~EGLContentBrowserClient() override;

      /* AUBIN : Many great stuff here to explore in the future !! */

      // Allows the embedder to set any number of custom BrowserMainParts
      // implementations for the browser startup code. See comments in
      // browser_main_parts.h.
      BrowserMainParts* CreateBrowserMainParts(
        const MainFunctionParams& parameters) override;

      // Returns the locale used by the application.
      // This is called on the UI and IO threads.
      std::string GetApplicationLocale() override;

      // Returns the languages used in the Accept-Languages HTTP header.
      // (Not called GetAcceptLanguages so it doesn't clash with win32).
      std::string GetAcceptLangs(BrowserContext* context) override;

      // Returns the default download directory.
      // This can be called on any thread.
      base::FilePath GetDefaultDownloadDirectory();

      // Returns the default filename used in downloads when we have no idea what
      // else we should do with the file.
      std::string GetDefaultDownloadName();

    private:

      EGLContent::BrowserConfig browser_config_;
      EGLContent::BrowserDelegate* delegate_;

      std::unique_ptr<EGLContentBrowserMainParts> browser_main_parts_;

  };

}

#endif // EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_
