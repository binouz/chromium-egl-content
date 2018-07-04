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

#include "base/path_service.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/trace_event/trace_log.h"

#include "content/common/content_constants_internal.h"
#include "content/public/common/content_switches.h"
#include "content/public/browser/browser_thread.h"
#include "content/browser/browser_main.h"

#include "ui/base/resource/resource_bundle.h"

#include "components/crash/content/app/breakpad_linux.h"

#include "content/eglcontent/content/content_main_delegate.h"
#include "content/eglcontent/content/content_client.h"
#include "content/eglcontent/content/content_browser_client.h"
#include "content/eglcontent/content/content_renderer_client.h"
#include "content/eglcontent/content/content_utility_client.h"

#include "content/eglcontent/browser/browser.h"

#include "content/eglcontent/api/main_delegate.h"

namespace content {

  EGLContentMainDelegate::EGLContentMainDelegate(
    EGLContent::MainDelegate* main_delegate,
    EGLContent::BrowserDelegate* browser_delegate,
    EGLContent::BrowserConfig& config)
    : browser_config_(config),
      main_delegate_(main_delegate),
      browser_delegate_(browser_delegate) {
  }

  EGLContentMainDelegate::~EGLContentMainDelegate() {
  }

  bool EGLContentMainDelegate::BasicStartupComplete(int* exit_code) {
    base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
    std::string process_type =
      command_line->GetSwitchValueASCII(switches::kProcessType);

    command_line->AppendSwitch(switches::kNoSandbox);

    content_client_.reset(new EGLContentClient(main_delegate_, browser_config_));
    SetContentClient(content_client_.get());

    return false;
  }

  void EGLContentMainDelegate::PreSandboxStartup() {
    base::FilePath pak_file;
    PathService::Get(base::DIR_MODULE, &pak_file);
    pak_file = pak_file.Append(FILE_PATH_LITERAL("egl_content.pak"));
    ui::ResourceBundle::InitSharedInstanceWithPakPath(pak_file);

    main_delegate_->BeforeSandboxing();
  }

  void EGLContentMainDelegate::SandboxInitialized(const std::string& process_type) {
    main_delegate_->AfterSandboxing();
  }

  int EGLContentMainDelegate::RunProcess(
    const std::string& process_type,
    const MainFunctionParams& main_function_params) {
    if (!process_type.empty())
      return -1;

    base::trace_event::TraceLog::GetInstance()->SetProcessName("Browser");
    base::trace_event::TraceLog::GetInstance()->SetProcessSortIndex(
      kTraceEventBrowserProcessSortIndex);

    std::unique_ptr<BrowserMainRunner> runner(BrowserMainRunner::Create());

    int exit_code = runner->Initialize(main_function_params);

    if (exit_code >= 0)
      return exit_code;

    exit_code = runner->Run();

    runner->Shutdown();

    return exit_code;
  }

  void EGLContentMainDelegate::ProcessExiting(const std::string& process_type) {
    ResourceBundle::CleanupSharedInstance();
  }

  void EGLContentMainDelegate::ZygoteForked() {
  }

  ContentBrowserClient* EGLContentMainDelegate::CreateContentBrowserClient() {
    browser_client_.reset(
      new EGLContentBrowserClient(browser_config_,
				  browser_delegate_));

    return browser_client_.get();
  }

  ContentRendererClient* EGLContentMainDelegate::CreateContentRendererClient() {
    renderer_client_.reset(new EGLContentRendererClient(main_delegate_));

    return renderer_client_.get();
  }

}
