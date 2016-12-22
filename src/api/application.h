#ifndef EGLCONTENT_API_APPLICATION_H_
# define EGLCONTENT_API_APPLICATION_H_

namespace EGLContent {

  class DisplayDelegate;
  class MainDelegate;
  class BrowserDelegate;
  struct BrowserConfig;

  class Application {

    public:

      virtual DisplayDelegate *CreateDisplayDelegate() = 0;
      virtual MainDelegate *CreateMainDelegate() = 0;
      virtual BrowserDelegate *CreateBrowserDelegate() = 0;
      virtual BrowserConfig& GetBrowserConfig() = 0;
  };

}

#endif /* !EGLCONTENT_API_APPLICATION_H_ */
