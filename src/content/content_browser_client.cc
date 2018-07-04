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

#include "content/eglcontent/api/browser_config.h"
#include "content/eglcontent/content/content_browser_client.h"
#include "content/eglcontent/browser/browser_main_parts.h"

namespace content {

  EGLContentBrowserClient::EGLContentBrowserClient(
    EGLContent::BrowserConfig& config,
    EGLContent::BrowserDelegate* delegate)
    : browser_config_(config),
      delegate_(delegate) {
  }

  EGLContentBrowserClient::~EGLContentBrowserClient() {
  }

  BrowserMainParts* EGLContentBrowserClient::CreateBrowserMainParts(
    const MainFunctionParams& parameters) {
    browser_main_parts_.reset(
      new EGLContentBrowserMainParts(browser_config_, delegate_));
    return browser_main_parts_.get();
  }

  std::string EGLContentBrowserClient::GetApplicationLocale() {
    return browser_config_.locale;
  }

  std::string EGLContentBrowserClient::GetAcceptLangs(BrowserContext* context) {
    return browser_config_.accept_language;
  }

  base::FilePath EGLContentBrowserClient::GetDefaultDownloadDirectory() {
    return base::FilePath(browser_config_.download_directory);
  }

  std::string EGLContentBrowserClient::GetDefaultDownloadName() {
    return browser_config_.download_name;
  }

}
