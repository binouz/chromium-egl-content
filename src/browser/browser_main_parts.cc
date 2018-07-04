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

  void EGLContentBrowserMainParts::PreEarlyInitialization() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
    // ui::InitializeInputMethodForTesting();
  }

  void EGLContentBrowserMainParts::PostEarlyInitialization() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

  void EGLContentBrowserMainParts::PreMainMessageLoopStart() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

  void EGLContentBrowserMainParts::PostMainMessageLoopStart() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

  void EGLContentBrowserMainParts::ToolkitInitialized() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

  void EGLContentBrowserMainParts::ServiceManagerConnectionStarted(
    ServiceManagerConnection* connection) {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

  void EGLContentBrowserMainParts::PreMainMessageLoopRun() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
    EGLContentBrowser::Initialise(browser_config_, delegate_);
  }

  void EGLContentBrowserMainParts::PostMainMessageLoopRun() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
    EGLContentBrowser::Release();
  }

  void EGLContentBrowserMainParts::PostDestroyThreads() {
    LOG(INFO) << "EGLContentBrowserMainParts::" << __FUNCTION__;
  }

}
