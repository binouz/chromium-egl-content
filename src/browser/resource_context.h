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

#ifndef EGLCONTENT_BROWSER_RESOURCE_CONTEXT_H_
# define EGLCONTENT_BROWSER_RESOURCE_CONTEXT_H_

#include "content/public/browser/resource_context.h"

namespace content {

  class EGLContentURLRequestContextGetter;

  class EGLContentResourceContext : public ResourceContext {

    public:

      EGLContentResourceContext();
      ~EGLContentResourceContext();

      net::HostResolver* GetHostResolver() override;

      net::URLRequestContext* GetRequestContext() override;

      void SetURLRequestContextGetter(
	EGLContentURLRequestContextGetter* getter);

    private:

      EGLContentURLRequestContextGetter* url_request_context_getter_;
  };

}

#endif /* !EGLCONTENT_BROWSER_RESOURCE_CONTEXT.H */
