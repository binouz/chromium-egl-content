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

#include "base/memory/ptr_util.h"
#include "base/threading/worker_pool.h"

#include "net/proxy/proxy_service.h"
#include "net/base/network_delegate_impl.h"
#include "net/ssl/channel_id_service.h"
#include "net/ssl/default_channel_id_store.h"
#include "net/ssl/ssl_config_service_defaults.h"
#include "net/cert/cert_verifier.h"
#include "net/cert/multi_log_ct_verifier.h"
#include "net/http/http_auth_handler_factory.h"
#include "net/http/http_server_properties_impl.h"
#include "net/http/http_cache.h"
#include "net/cookies/cookie_store.h"
#include "net/url_request/url_request_context_storage.h"
#include "net/url_request/static_http_user_agent_settings.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_job_factory_impl.h"
#include "net/url_request/data_protocol_handler.h"
#include "net/url_request/file_protocol_handler.h"
#include "net/url_request/url_request_intercepting_job_factory.h"

#include "content/public/browser/browser_thread.h"
#include "content/public/browser/cookie_store_factory.h"

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
      request_interceptors_(std::move(request_interceptors)) {
    proxy_config_service_ = net::ProxyService::CreateSystemProxyConfigService(
      BrowserThread::GetTaskRunnerForThread(BrowserThread::IO),
      BrowserThread::GetTaskRunnerForThread(BrowserThread::FILE));
    std::swap(protocol_handlers_, *protocol_handlers);
  }

  EGLContentURLRequestContextGetter::~EGLContentURLRequestContextGetter() {
  }

  net::URLRequestContext* EGLContentURLRequestContextGetter::GetURLRequestContext() {
    DCHECK_CURRENTLY_ON(BrowserThread::IO);

    if (!url_request_context_) {
      url_request_context_.reset(new net::URLRequestContext());
      network_delegate_.reset(new net::NetworkDelegateImpl());
      url_request_context_->set_network_delegate(network_delegate_.get());

      storage_.reset(
        new net::URLRequestContextStorage(url_request_context_.get()));
      storage_->set_cookie_store(CreateCookieStore(CookieStoreConfig()));
      storage_->set_channel_id_service(
	base::WrapUnique(
	  new net::ChannelIDService(
	    new net::DefaultChannelIDStore(NULL),
	    base::WorkerPool::GetTaskRunner(true))));
      storage_->set_http_user_agent_settings(
        base::MakeUnique<net::StaticHttpUserAgentSettings>(
	  accept_language_, user_agent_));

      std::unique_ptr<net::HostResolver> host_resolver(
        net::HostResolver::CreateDefaultResolver(NULL));

      storage_->set_cert_verifier(net::CertVerifier::CreateDefault());
      storage_->set_transport_security_state(
        base::WrapUnique(new net::TransportSecurityState));
      storage_->set_cert_transparency_verifier(
        base::WrapUnique(new net::MultiLogCTVerifier));
      storage_->set_ct_policy_enforcer(
        base::WrapUnique(new net::CTPolicyEnforcer));
      storage_->set_proxy_service(
	net::ProxyService::CreateUsingSystemProxyResolver(
	  std::move(proxy_config_service_), 0, NULL));
      storage_->set_ssl_config_service(new net::SSLConfigServiceDefaults());
      storage_->set_http_auth_handler_factory(
        net::HttpAuthHandlerFactory::CreateDefault(host_resolver.get()));
      storage_->set_http_server_properties(
        base::MakeUnique<net::HttpServerPropertiesImpl>());

      std::unique_ptr<net::HttpCache::DefaultBackend> main_backend(
        new net::HttpCache::DefaultBackend(
	  net::DISK_CACHE,
	  net::CACHE_BACKEND_DEFAULT,
	  cache_path_, 0,
	  BrowserThread::GetTaskRunnerForThread(BrowserThread::CACHE)));

      net::HttpNetworkSession::Params network_session_params;
      network_session_params.cert_verifier =
        url_request_context_->cert_verifier();
      network_session_params.transport_security_state =
        url_request_context_->transport_security_state();
      network_session_params.cert_transparency_verifier =
        url_request_context_->cert_transparency_verifier();
      network_session_params.ct_policy_enforcer =
        url_request_context_->ct_policy_enforcer();
      network_session_params.channel_id_service =
        url_request_context_->channel_id_service();
      network_session_params.proxy_service =
        url_request_context_->proxy_service();
      network_session_params.ssl_config_service =
        url_request_context_->ssl_config_service();
      network_session_params.http_auth_handler_factory =
        url_request_context_->http_auth_handler_factory();
      network_session_params.http_server_properties =
        url_request_context_->http_server_properties();
      network_session_params.net_log =
        url_request_context_->net_log();
      network_session_params.ignore_certificate_errors =
        true;

      // Give |storage_| ownership at the end in case it's |mapped_host_resolver|.
      storage_->set_host_resolver(std::move(host_resolver));
      network_session_params.host_resolver =
        url_request_context_->host_resolver();

      storage_->set_http_network_session(
        base::MakeUnique<net::HttpNetworkSession>(network_session_params));
      storage_->set_http_transaction_factory(
	base::MakeUnique<net::HttpCache>(
	  storage_->http_network_session(), std::move(main_backend),
	  true /* set_up_quic_server_info */));

      std::unique_ptr<net::URLRequestJobFactoryImpl> job_factory(
        new net::URLRequestJobFactoryImpl());

      for (ProtocolHandlerMap::iterator it =
	     protocol_handlers_.begin();
	   it != protocol_handlers_.end();
	   ++it) {
        job_factory->SetProtocolHandler(
	  it->first, base::WrapUnique(it->second.release()));
      }

      job_factory->SetProtocolHandler(
        url::kDataScheme, base::WrapUnique(new net::DataProtocolHandler));
      job_factory->SetProtocolHandler(
        url::kFileScheme,
        base::MakeUnique<net::FileProtocolHandler>(
	  BrowserThread::GetBlockingPool()->GetTaskRunnerWithShutdownBehavior(
	    base::SequencedWorkerPool::SKIP_ON_SHUTDOWN)));

      std::unique_ptr<net::URLRequestJobFactory> top_job_factory =
        std::move(job_factory);
      for (URLRequestInterceptorScopedVector::reverse_iterator i =
             request_interceptors_.rbegin();
	   i != request_interceptors_.rend();
	   ++i) {
	top_job_factory.reset(
	  new net::URLRequestInterceptingJobFactory(
	    std::move(top_job_factory), base::WrapUnique(*i)));
      }
      request_interceptors_.weak_clear();

      storage_->set_job_factory(std::move(top_job_factory));
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
