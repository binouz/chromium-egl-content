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

#include "application.h"
#include "display_delegate.h"
#include "browser_delegate.h"
#include "main_delegate.h"

DemoApp::DemoApp() {
  config_.cache_path = "/tmp/eglcontent-cache";
  config_.download_directory = "/tmp/eglcontent-download";
  config_.download_name = "eglcontent";
  config_.locale = "en-us";
  config_.product_name = "eglcontent";
  config_.user_agent = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.59 Safari/537.36";
  config_.accept_language;
  config_.screen_width = 1280;
  config_.screen_height = 720;
  config_.scale_factor = 1.0;
}

DemoApp::~DemoApp() {
}

EGLContent::DisplayDelegate *DemoApp::CreateDisplayDelegate() {
  return new DemoDisplayDelegate(1280, 720);
}

EGLContent::MainDelegate *DemoApp::CreateMainDelegate() {
  return new DemoMainDelegate();
}

EGLContent::BrowserDelegate *DemoApp::CreateBrowserDelegate() {
  return new DemoBrowserDelegate();
}

EGLContent::BrowserConfig& DemoApp::GetBrowserConfig() {
  return config_;
}
