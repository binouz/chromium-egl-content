#ifndef APPLICATION_H_
# define APPLICATION_H_

#include <eglcontent/application.h>
#include <eglcontent/browser_config.h>

class DemoApp : public EGLContent::Application {

  public:
    DemoApp();
    ~DemoApp();

    EGLContent::DisplayDelegate *CreateDisplayDelegate() override;
    EGLContent::MainDelegate *CreateMainDelegate() override;
    EGLContent::BrowserDelegate *CreateBrowserDelegate() override;

    EGLContent::BrowserConfig& GetBrowserConfig() override;

  private:

    EGLContent::BrowserConfig config_;

};

#endif /* !APPLICATION.H */
