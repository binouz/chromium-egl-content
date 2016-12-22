#ifndef MAIN_DELEGATE_H_
# define MAIN_DELEGATE_H_

#include <string>

#include <eglcontent/main_delegate.h>

class DemoMainDelegate : public EGLContent::MainDelegate {

  public:
    DemoMainDelegate();
    ~DemoMainDelegate();

    void OnStartupComplete() override;
    void BeforeSandboxing() override;
    void AfterSandboxing() override;

};

#endif /* !MAIN_DELEGATE.H */
