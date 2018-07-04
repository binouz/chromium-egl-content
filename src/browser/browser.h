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

#ifndef EGLCONTENT_BROWSER_BROWSER_H_
# define EGLCONTENT_BROWSER_BROWSER_H_

#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_delegate.h"

#include "content/eglcontent/api/browser_delegate.h"

namespace EGLContent {
  class Application;
  struct BrowserConfig;
}

namespace content {

  class EGLContentBrowserContext;
  class EGLContentAuraScreen;

  class EGLContentBrowser : public WebContentsDelegate,
			    public EGLContent::BrowserDelegate::Controller {

    public:

      ~EGLContentBrowser();

      static void Initialise(EGLContent::BrowserConfig& config,
			     EGLContent::BrowserDelegate* delegate);
      static void Release();

      // WebContentsDelegate
      void LoadingStateChanged(WebContents* source, bool to_different_document) override;
      void LoadProgressChanged(WebContents* source, double progress) override;
      void UpdateTargetURL(WebContents* source, const GURL& url) override;

      // EGLContent::BrowserDelegate::Controller
      void LoadURL(std::string& url) override;
      void Stop() override;
      void Reload() override;
      std::string GetURL() override;
      bool IsLoading() override;
      bool IsAudioMuted() override;
      void SetAudioMuted(bool mute) override;
      bool IsCrashed() const override;

    private:

      EGLContentBrowser(EGLContent::BrowserDelegate* delegate);

      void CreateBrowserContext(EGLContent::BrowserConfig& config);
      void CreateWindow(EGLContent::BrowserConfig& config);
      void Ready();

      static std::unique_ptr<EGLContentBrowser> g_browser;

      std::unique_ptr<EGLContentAuraScreen> screen_;
      std::unique_ptr<EGLContentBrowserContext> browser_context_;
      std::unique_ptr<WebContents> web_contents_;

      EGLContent::BrowserDelegate* delegate_;
  };
}

#endif /* !EGLCONTENT_BROWSER_BROWSER.H */
