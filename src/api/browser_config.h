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

#ifndef BROWSER_H_
# define BROWSER_H_

#include <string>

namespace EGLContent {

  struct BrowserConfig {
    BrowserConfig()
      : cache_path(""),
        download_directory(""),
        download_name(""),
        locale(""),
        product_name(""),
        user_agent(""),
        accept_language(""),
        screen_width(0),
        screen_height(0),
        scale_factor(1) {}
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
