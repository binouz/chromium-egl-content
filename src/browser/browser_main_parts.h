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

#ifndef EGLCONTENT_BROWSER_BROWSER_MAIN_PARTS_H_
# define EGLCONTENT_BROWSER_BROWSER_MAIN_PARTS_H_

#include "content/public/browser/browser_main_parts.h"

#include "content/eglcontent/api/browser_config.h"
#include "content/eglcontent/api/browser_delegate.h"

namespace content {

  class EGLContentBrowserMainParts : public BrowserMainParts {

    public:

      EGLContentBrowserMainParts(EGLContent::BrowserConfig& config,
				 EGLContent::BrowserDelegate* delegate);
      ~EGLContentBrowserMainParts();

      int PreEarlyInitialization() override;

      void PostEarlyInitialization() override;

      void PreMainMessageLoopStart() override;

      void PostMainMessageLoopStart() override;

      // Allows an embedder to do any extra toolkit initialization.
      void ToolkitInitialized() override;

      void ServiceManagerConnectionStarted(
	ServiceManagerConnection* connection) override;

      // This is called just before the main message loop is run.  The
      // various browser threads have all been created at this point
      void PreMainMessageLoopRun() override;

      // This happens after the main message loop has stopped, but before
      // threads are stopped.
      void PostMainMessageLoopRun() override;

      // Called as the very last part of shutdown, after threads have been
      // stopped and destroyed.
      void PostDestroyThreads() override;

    private :

      EGLContent::BrowserConfig browser_config_;
      EGLContent::BrowserDelegate* delegate_;
  };

}


#endif /* !EGLCONTENT_BROWSER_BROWSER_MAIN_PARTS_H_ */
