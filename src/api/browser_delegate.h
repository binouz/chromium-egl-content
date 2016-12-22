#ifndef EGLCONTENT_API_BROWSER_DELEGATE_H_
# define EGLCONTENT_API_BROWSER_DELEGATE_H_

namespace EGLContent {

  class BrowserDelegate {

    public:

      class Controller {

	public:

	  virtual void LoadURL(std::string& url) = 0;
      };

      BrowserDelegate() {}
      ~BrowserDelegate() {}

      virtual void LoadingStateChanged(bool loading) {}
      virtual void LoadProgressed(double progress) {}
      virtual void TargetURLChanged(std::string& url) {}

      virtual void BrowserCreated(Controller* controller) {};
  };

}


#endif /* !BROWSER_DELEGATE.H */
