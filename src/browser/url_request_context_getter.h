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

#ifndef EGLCONTENT_BROWSER_URL_REQUEST_CONTEXT_GETTER_H_
# define EGLCONTENT_BROWSER_URL_REQUEST_CONTEXT_GETTER_H_

#include "base/files/file_path.h"

#include "net/url_request/url_request_context_getter.h"

#include "content/public/browser/browser_context.h"

namespace net {
  class HostResolver;
  class ProxyConfigService;
  class NetworkDelegate;
  class URLRequestContextStorage;
}

namespace content {

  class EGLContentURLRequestContextGetter : public net::URLRequestContextGetter {

    public:

      EGLContentURLRequestContextGetter(ProtocolHandlerMap* protocol_handlers,
					URLRequestInterceptorScopedVector request_interceptors,
				        base::FilePath& cache_path,
					std::string& accept_language,
					std::string& user_agent);
      ~EGLContentURLRequestContextGetter();

      // Returns the URLRequestContextGetter's URLRequestContext. Must only be
      // called on the network task runner. Once NotifyContextShuttingDown() is
      // invoked, must always return nullptr. Does not transfer ownership of
      // the URLRequestContext.
      net::URLRequestContext* GetURLRequestContext() override;

      // Returns a SingleThreadTaskRunner corresponding to the thread on
      // which the network IO happens (the thread on which the returned
      // URLRequestContext may be used).
      scoped_refptr<base::SingleThreadTaskRunner> GetNetworkTaskRunner() const override;

      net::HostResolver* GetHostResolver();

    private:

      std::string accept_language_;
      base::FilePath cache_path_;
      std::string user_agent_;

      ProtocolHandlerMap protocol_handlers_;
      URLRequestInterceptorScopedVector request_interceptors_;

      std::unique_ptr<net::ProxyConfigService> proxy_config_service_;
      std::unique_ptr<net::NetworkDelegate> network_delegate_;
      std::unique_ptr<net::URLRequestContextStorage> storage_;
      std::unique_ptr<net::URLRequestContext> url_request_context_;

  };

}

#endif /* !EGLCONTENT_BROWSER_URL_REQUEST_CONTEXT_GETTER.H */
