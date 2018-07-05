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

#ifndef COMMAND_LINE_INTERFACE_H_
# define COMMAND_LINE_INTERFACE_H_

#include <string>
#include <thread>

#include <eglcontent/browser_delegate.h>

class CommandLineInterface {

  public:
    CommandLineInterface();
    ~CommandLineInterface();

    void Initialise(
      EGLContent::BrowserDelegate::Controller* controller);
    void Run();

    void LoadingStateChanged(bool loading);
    void LoadProgressed(double progress);
    void TargetURLChanged(std::string& url);

  private:

    EGLContent::BrowserDelegate::Controller* controller_;
    std::thread thread_;
};

#endif /* !COMMAND_LINE_INTERFACE.H */
