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

#include "base/command_line.h"
#include "base/memory/ptr_util.h"
#include "base/single_thread_task_runner.h"

#include "components/network_session_configurator/browser/network_session_configurator.h"

#include "net/cert/cert_verifier.h"
#include "net/cert/ct_policy_enforcer.h"
#include "net/cert/ct_policy_status.h"
#include "net/cert/do_nothing_ct_verifier.h"
#include "net/cookies/cookie_store.h"
#include "net/http/http_network_session.h"
#include "net/proxy_resolution/proxy_config_service.h"
#include "net/base/network_delegate_impl.h"
#include "net/ssl/channel_id_service.h"
#include "net/ssl/default_channel_id_store.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_context_builder.h"
#include "services/network/public/cpp/features.h"
#include "services/network/public/cpp/network_switches.h"
#include "url/url_constants.h"

#include "content/public/browser/browser_thread.h"
#include "content/public/browser/cookie_store_factory.h"
#include "content/public/common/content_switches.h"

#include "content/eglcontent/browser/url_request_context_getter.h"

namespace content {

  EGLContentURLRequestContextGetter::EGLContentURLRequestContextGetter(
    ProtocolHandlerMap* protocol_handlers,
    URLRequestInterceptorScopedVector request_interceptors,
    base::FilePath& cache_path,
    std::string& accept_language,
    std::string& user_agent)
    : accept_language_(accept_language),
      cache_path_(cache_path),
      user_agent_(user_agent),
      request_interceptors_(std::move(request_interceptors)),
      io_task_runner_(
        std::move(BrowserThread::GetTaskRunnerForThread(BrowserThread::IO))) {
    std::swap(protocol_handlers_, *protocol_handlers);
  }

  EGLContentURLRequestContextGetter::~EGLContentURLRequestContextGetter() {
  }

  net::URLRequestContext* EGLContentURLRequestContextGetter::GetURLRequestContext() {
    DCHECK_CURRENTLY_ON(BrowserThread::IO);

    if (!url_request_context_) {
      const base::CommandLine& command_line =
        *base::CommandLine::ForCurrentProcess();
      std::unique_ptr<net::CookieStore> cookie_store =
        CreateCookieStore(CookieStoreConfig());
      std::unique_ptr<net::ChannelIDService> channel_id_service =
        std::make_unique<net::ChannelIDService>(
          new net::DefaultChannelIDStore(nullptr));
      cookie_store->SetChannelIDServiceID(channel_id_service->GetUniqueID());

      std::unique_ptr<net::ProxyConfigService> proxy_config_service =
        net::ProxyResolutionService::CreateSystemProxyConfigService(io_task_runner_);

      net::URLRequestContextBuilder::HttpCacheParams cache_params;
      cache_params.path = cache_path_;
      cache_params.type = net::URLRequestContextBuilder::HttpCacheParams::DISK;

      net::HttpNetworkSession::Params network_session_params;
      network_session_configurator::ParseCommandLineAndFieldTrials(
        command_line, false, user_agent_, &network_session_params);

      net::URLRequestContextBuilder builder;
      // TODO :
      // builder.set_net_log(net_log_);
      // builder.set_network_delegate(CreateNetworkDelegate());
      builder.SetCookieAndChannelIdStores(std::move(cookie_store),
                                          std::move(channel_id_service));
      builder.set_accept_language(accept_language_);
      builder.set_user_agent(user_agent_);
      builder.SetCertVerifier(net::CertVerifier::CreateDefault());
      builder.set_proxy_config_service(std::move(proxy_config_service));
      builder.EnableHttpCache(cache_params);
      builder.set_http_network_session_params(network_session_params);
      builder.set_data_enabled(true);
      builder.set_file_enabled(true);
      builder.set_enable_brotli(true);

      for (ProtocolHandlerMap::iterator it =
	     protocol_handlers_.begin();
	   it != protocol_handlers_.end();
	   ++it) {
        builder.SetProtocolHandler(
          it->first,
          std::move(it->second));
      }

      builder.SetInterceptors(std::move(request_interceptors_));

      url_request_context_ = builder.Build();
    }

    return url_request_context_.get();
  }

  scoped_refptr<base::SingleThreadTaskRunner>
  EGLContentURLRequestContextGetter::GetNetworkTaskRunner() const {
    return BrowserThread::GetTaskRunnerForThread(BrowserThread::IO);
  }

  net::HostResolver* EGLContentURLRequestContextGetter::GetHostResolver() {
    return url_request_context_->host_resolver();
  }
}
