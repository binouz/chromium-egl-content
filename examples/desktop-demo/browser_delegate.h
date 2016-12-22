#ifndef BROWSER_DELEGATE_H_
# define BROWSER_DELEGATE_H_

#include <eglcontent/browser_delegate.h>

class DemoBrowserDelegate : public EGLContent::BrowserDelegate {

  public:

    DemoBrowserDelegate();
    ~DemoBrowserDelegate();

    void BrowserCreated(EGLContent::BrowserDelegate::Controller* controller) override;

  private:

};

#endif /* !BROWSER_DELEGATE.H */
