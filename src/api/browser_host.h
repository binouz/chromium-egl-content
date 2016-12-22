#ifndef BROWSER_H_
# define BROWSER_H_

#include <string>

namespace EGLContent {

  class BrowserHost {

    public :

      virtual void LoadURL(std::string url) = 0;

  };

}

#endif /* !BROWSER.H */
