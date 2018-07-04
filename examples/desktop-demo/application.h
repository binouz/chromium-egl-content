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

#ifndef APPLICATION_H_
# define APPLICATION_H_

#include <eglcontent/application.h>
#include <eglcontent/browser_config.h>

class DemoApp : public EGLContent::Application {

  public:
    DemoApp();
    ~DemoApp();

    EGLContent::DisplayDelegate *CreateDisplayDelegate() override;
    EGLContent::MainDelegate *CreateMainDelegate() override;
    EGLContent::BrowserDelegate *CreateBrowserDelegate() override;

    EGLContent::BrowserConfig& GetBrowserConfig() override;

  private:

    EGLContent::BrowserConfig config_;

};

#endif /* !APPLICATION.H */
