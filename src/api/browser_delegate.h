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

#ifndef EGLCONTENT_API_BROWSER_DELEGATE_H_
# define EGLCONTENT_API_BROWSER_DELEGATE_H_

namespace EGLContent {

  class BrowserDelegate {

    public:

      class Controller {

	public:

	  virtual void LoadURL(std::string& url) = 0;
      };

      BrowserDelegate() {}
      ~BrowserDelegate() {}

      virtual void LoadingStateChanged(bool loading) {}
      virtual void LoadProgressed(double progress) {}
      virtual void TargetURLChanged(std::string& url) {}

      virtual void BrowserCreated(Controller* controller) {};
  };

}


#endif /* !BROWSER_DELEGATE.H */
