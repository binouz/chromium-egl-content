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

#include "content/eglcontent/browser/browser.h"
#include "content/eglcontent/browser/browser_main_parts.h"

namespace content {

  EGLContentBrowserMainParts::EGLContentBrowserMainParts(
    EGLContent::BrowserConfig& config,
    EGLContent::BrowserDelegate* delegate)
    : browser_config_(config),
      delegate_(delegate) {
  }

  EGLContentBrowserMainParts::~EGLContentBrowserMainParts(){
  }

  int EGLContentBrowserMainParts::PreEarlyInitialization() {
    // ui::InitializeInputMethodForTesting();
    return 0;
  }

  void EGLContentBrowserMainParts::PostEarlyInitialization() {
  }

  void EGLContentBrowserMainParts::PreMainMessageLoopStart() {
  }

  void EGLContentBrowserMainParts::PostMainMessageLoopStart() {
  }

  void EGLContentBrowserMainParts::ToolkitInitialized() {
  }

  void EGLContentBrowserMainParts::ServiceManagerConnectionStarted(
    ServiceManagerConnection* connection) {
  }

  void EGLContentBrowserMainParts::PreMainMessageLoopRun() {
    EGLContentBrowser::Initialise(browser_config_, delegate_);
  }

  void EGLContentBrowserMainParts::PostMainMessageLoopRun() {
    EGLContentBrowser::Release();
  }

  void EGLContentBrowserMainParts::PostDestroyThreads() {
  }

}
