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

#include "base/bind.h"
#include "base/command_line.h"

#include "content/public/app/content_main.h"
#include "content/public/app/content_main_runner.h"
#include "content/app/content_service_manager_main_delegate.h"

#include "content/public/browser/browser_thread.h"

#include "content/public/common/content_switches.h"

#include "services/service_manager/embedder/main.h"

#include "ui/ozone/platform/eglcontent/eglcontent_interface.h"

#include "content/eglcontent/content/content_main_delegate.h"

#include "content/eglcontent/browser/browser.h"

#include "content/eglcontent/api/eglcontent.h"
#include "content/eglcontent/api/main_delegate.h"
#include "content/eglcontent/api/browser_delegate.h"
#include "content/eglcontent/api/display_delegate.h"
#include "content/eglcontent/api/application.h"
#include "content/eglcontent/api/browser_config.h"

#include <memory>

namespace EGLContent {

  class EGLContentServiceManagerMainDelegate :
      public content::ContentServiceManagerMainDelegate {

    public:

      EGLContentServiceManagerMainDelegate(

        Application *app, const content::ContentMainParams& params)
        : content::ContentServiceManagerMainDelegate(params),
          application_(app) {}

      ~EGLContentServiceManagerMainDelegate() override = default;

      int Initialize(const InitializeParams& params) override {
        base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
        std::string process_type =
          command_line->GetSwitchValueASCII(switches::kProcessType);
        int result = content::ContentServiceManagerMainDelegate::Initialize(params);

        if (result >= 0) {
          LOG(WARNING)
            << "content::ContentServiceManagerMainDelegate::Initialize failed : "
            << result;
          return result;
        }

        if (process_type == switches::kGpuProcess ||
            command_line->HasSwitch(switches::kSingleProcess) ||
            command_line->HasSwitch(switches::kInProcessGPU))
          ui::EGLContentInterface::SetDisplayDelegate(
            application_->CreateDisplayDelegate());

        return result;
      }

    private:
      Application *application_;
  };

  int __attribute__((visibility("default"))) Run(
    Application *app, int argc, const char **argv) {
    EGLContent::BrowserConfig config;

    app->GetBrowserConfig(config);

    LOG(INFO) << "cache_path=" << config.cache_path;
    LOG(INFO) << "accept_language=" << config.accept_language;
    LOG(INFO) << "user_agent=" << config.user_agent;

    content::EGLContentMainDelegate content_delegate(
      app->CreateMainDelegate(), app->CreateBrowserDelegate(), config);
    content::ContentMainParams content_params(&content_delegate);

    content_params.argc = argc;
    content_params.argv = argv;

    EGLContentServiceManagerMainDelegate service_delegate(app, content_params);
    service_manager::MainParams service_params(&service_delegate);

    service_params.argc = argc;
    service_params.argv = argv;

    return service_manager::Main(service_params);
  }

}
