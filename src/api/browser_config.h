#ifndef BROWSER_H_
# define BROWSER_H_

#include <string>

namespace EGLContent {

  struct BrowserConfig {
    BrowserConfig() {}
    ~BrowserConfig() {}

    std::string cache_path;
    std::string download_directory;
    std::string download_name;
    std::string locale;
    std::string product_name;
    std::string user_agent;
    std::string accept_language;

    int screen_width;
    int screen_height;
    float scale_factor;
  };

}

#endif /* !BROWSER.H */
