#ifndef EGLCONTENT_API_MAIN_DELEGATE_H_
# define EGLCONTENT_API_MAIN_DELEGATE_H_

namespace EGLContent {

  class BrowserHost;

  class MainDelegate {

    public:

      virtual void OnStartupComplete() = 0;
      virtual void BeforeSandboxing() = 0;
      virtual void AfterSandboxing() = 0;

  };

}

#endif /* !EGLCONTENT_API_MAIN_DELEGATE_H_ */
