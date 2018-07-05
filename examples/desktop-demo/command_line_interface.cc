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

#include <iostream>
#include <vector>

#include "command_line_interface.h"

namespace {
  class CommandLineParser {

    public:

      CommandLineParser() {
      }

      ~CommandLineParser() {
      }

      void Parse(std::string& str) {
	bool cmd = true;
	std::string s = str;
	size_t pos = 0;

	parameters_.clear();

	while ((pos = s.find(" ")) != std::string::npos) {
	  if (cmd) {
	    command_ = s.substr(0, pos);
	    cmd = false;
	  } else
	    parameters_.push_back(s.substr(0, pos));
	  s.erase(0, pos + 1);
	}

	if (cmd)
	  command_ = str;
	else if (!s.empty())
	  parameters_.push_back(s);
      }

      std::string& Command() {
	return command_;
      }

      int ParameterSize() {
	return parameters_.size();
      }

      std::string& GetStringParameter(int pos) {
	return parameters_[pos];
      }

      static std::string EXIT;
      static std::string LOAD;
      static std::string STOP;
      static std::string RELOAD;
      static std::string GET_URL;
      static std::string HELP;

    private:

      std::string command_;
      std::vector<std::string> parameters_;

  };

  std::string CommandLineParser::EXIT    = "exit";
  std::string CommandLineParser::LOAD    = "load";
  std::string CommandLineParser::STOP    = "stop";
  std::string CommandLineParser::RELOAD  = "reload";
  std::string CommandLineParser::GET_URL = "get_url";
  std::string CommandLineParser::HELP    = "help";

  static void ThreadTrampoline(CommandLineInterface* interface) {
    interface->Run();
  }
}

CommandLineInterface::CommandLineInterface()
  : controller_(NULL) {
}

CommandLineInterface::~CommandLineInterface() {
}

void CommandLineInterface::Initialise(
  EGLContent::BrowserDelegate::Controller* controller) {
  controller_ = controller;
  thread_ = std::thread(ThreadTrampoline, this);
}

void CommandLineInterface::LoadingStateChanged(bool loading) {
  std::cout << "\rLoading state changed : "
	    << (loading ? "START" : "END") << std::endl
	    <<  "> " << std::flush;
}

void CommandLineInterface::LoadProgressed(double progress) {
  std::cout << "\rLoading progress : " << progress << "%" << std::endl
	    <<  "> " << std::flush;
}

void CommandLineInterface::TargetURLChanged(std::string& url) {
  std::cout << "\rURL changed : " << url << std::endl
	    <<  "> " << std::flush;
}

void CommandLineInterface::Run() {
  CommandLineParser parser;

  while (1) {
    std::string str;

    std::cout << "> " << std::flush;
    std::getline(std::cin, str);

    parser.Parse(str);

    std::string& cmd = parser.Command();
    if (cmd == CommandLineParser::EXIT) {
      // TODO
    } else if (cmd == CommandLineParser::LOAD) {
      if (parser.ParameterSize() == 1)
	controller_->LoadURL(parser.GetStringParameter(0));
      else
	std::cout << "Usage : load <url>" << std::endl;
    } else if (cmd == CommandLineParser::STOP) {
      controller_->Stop();
    } else if (cmd == CommandLineParser::RELOAD) {
      controller_->Reload();
    } else if (cmd == CommandLineParser::GET_URL) {
      std::cout << "Current URL : " << controller_->GetURL() << std::endl;
    } else {
      if (cmd != CommandLineParser::HELP)
	std::cout << "Unknown command " << cmd << std::endl;
      else
	std::cout << "Help :" << std::endl;
      std::cout << "- exit : exit program" << std::endl;
      std::cout << "- load <url> : load <url> in browser" << std::endl;
      std::cout << "- stop : stop current URL loading" << std::endl;
      std::cout << "- reload : reload current page" << std::endl;
      std::cout << "- get_url : print current URL" << std::endl;
      std::cout << "- help : display this help" << std::endl;
    }
  }
}
