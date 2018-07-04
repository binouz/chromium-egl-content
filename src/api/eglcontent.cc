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

#include "content/public/browser/browser_thread.h"

#include "content/public/common/content_switches.h"

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

  int __attribute__((visibility("default"))) Run(
    Application *app, int argc, const char **argv) {
    int exit_code;

    base::CommandLine command_line(base::CommandLine::NO_PROGRAM);
    command_line.InitFromArgv(argc, argv);

    std::string process_type =
      command_line.GetSwitchValueASCII(switches::kProcessType);

    content::EGLContentMainDelegate* delegate = new content::EGLContentMainDelegate(
      app->CreateMainDelegate(), app->CreateBrowserDelegate(), app->GetBrowserConfig());

    content::ContentMainRunner* runner = content::ContentMainRunner::Create();
    content::ContentMainParams params(delegate);

    params.argc = argc;
    params.argv = argv;

    exit_code = runner->Initialize(params);
    if (exit_code >= 0) {
      LOG(WARNING) << "ContentMainRunner initialization failed : " << exit_code;
      return exit_code;
    }

    if (process_type == switches::kGpuProcess ||
	command_line.HasSwitch(switches::kSingleProcess) ||
	command_line.HasSwitch(switches::kInProcessGPU))
      ui::EGLContentInterface::SetDisplayDelegate(app->CreateDisplayDelegate());

    exit_code = runner->Run();

    return exit_code;
  }

}
