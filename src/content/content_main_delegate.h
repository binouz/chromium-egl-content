#ifndef EGLCONTENT_CONTENT_CONTENT_MAIN_DELEGATE_H_
# define EGLCONTENT_CONTENT_CONTENT_MAIN_DELEGATE_H_

#include "base/macros.h"
#include "base/files/file_path.h"

#include "content/public/common/content_client.h"
#include "content/public/app/content_main_delegate.h"
#include "content/public/browser/browser_main_runner.h"

#include "content/eglcontent/api/browser_config.h"
#include "content/eglcontent/api/browser_delegate.h"

#include <memory>

namespace EGLContent {
  class MainDelegate;
}

namespace content {

  class EGLContentBrowser;

  class EGLContentMainDelegate : public ContentMainDelegate {

    public:
      EGLContentMainDelegate(EGLContent::MainDelegate* main_delegate,
			     EGLContent::BrowserDelegate* browser_delegate,
			     EGLContent::BrowserConfig& config);
      ~EGLContentMainDelegate() override;

      // Tells the embedder that the absolute basic startup has been done, i.e.
      // it's now safe to create singletons and check the command line. Return true
      // if the process should exit afterwards, and if so, |exit_code| should be
      // set. This is the place for embedder to do the things that must happen at
      // the start. Most of its startup code should be in the methods below.
      bool BasicStartupComplete(int* exit_code) override;

      // This is where the embedder puts all of its startup code that needs to run
      // before the sandbox is engaged.
      void PreSandboxStartup() override;

      // This is where the embedder can add startup code to run after the sandbox
      // has been initialized.
      void SandboxInitialized(const std::string& process_type) override;

      // Asks the embedder to start a process. Return -1 for the default behavior.
      int RunProcess(
        const std::string& process_type,
        const MainFunctionParams& main_function_params) override;

      // Called right before the process exits.
      void ProcessExiting(const std::string& process_type) override;

      // Called every time the zygote process forks.
      void ZygoteForked() override;

      // Called once per relevant process type to allow the embedder to customize
      // content. If an embedder wants the default (empty) implementation, don't
      // override this.
      ContentBrowserClient* CreateContentBrowserClient() override;
      ContentRendererClient* CreateContentRendererClient() override;
    private:

      EGLContent::BrowserConfig browser_config_;

      std::unique_ptr<ContentClient> content_client_;
      std::unique_ptr<ContentBrowserClient> browser_client_;
      std::unique_ptr<ContentRendererClient> renderer_client_;
      std::unique_ptr<EGLContentBrowser> browser_;

      EGLContent::MainDelegate* main_delegate_;
      EGLContent::BrowserDelegate* browser_delegate_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentMainDelegate);
  };

}

#endif // EGLCONTENT_CONTENT_CONTENT_MAIN_DELEGATE_H_
