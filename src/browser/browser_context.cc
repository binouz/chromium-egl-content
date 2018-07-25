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

#include "components/guest_view/browser/guest_view_manager.h"

#include "content/eglcontent/api/browser_config.h"

#include "content/eglcontent/browser/browser_context.h"

namespace content {
  EGLContentBrowserContext::EGLContentBrowserContext(
    EGLContent::BrowserConfig& config)
    : cache_path_(base::FilePath(config.cache_path)),
      accept_language_(config.accept_language),
      user_agent_(config.user_agent) {
  }

  EGLContentBrowserContext::~EGLContentBrowserContext() {
  }

  void EGLContentBrowserContext::Initialise() {
    BrowserContext::Initialize(this, cache_path_);
    resource_context_.reset(new EGLContentResourceContext());
  }

  std::unique_ptr<ZoomLevelDelegate> EGLContentBrowserContext::CreateZoomLevelDelegate(
    const base::FilePath& partition_path) {
    return std::unique_ptr<ZoomLevelDelegate>();
  }

  base::FilePath EGLContentBrowserContext::GetPath() const {
    return cache_path_;
  }

  bool EGLContentBrowserContext::IsOffTheRecord() const {
    return false;
  }

  ResourceContext* EGLContentBrowserContext::GetResourceContext() {
    return resource_context_.get();
  }

  DownloadManagerDelegate* EGLContentBrowserContext::GetDownloadManagerDelegate() {
    return NULL;
  }

  BrowserPluginGuestManager* EGLContentBrowserContext::GetGuestManager() {
    return guest_view::GuestViewManager::FromBrowserContext(this);
  }

  storage::SpecialStoragePolicy* EGLContentBrowserContext::GetSpecialStoragePolicy() {
    return NULL;
  }

  PushMessagingService* EGLContentBrowserContext::GetPushMessagingService() {
    return NULL;
  }

  SSLHostStateDelegate* EGLContentBrowserContext::GetSSLHostStateDelegate() {
    return NULL;
  }

  PermissionManager* EGLContentBrowserContext::GetPermissionManager() {
    return NULL;
  }

  BackgroundSyncController* EGLContentBrowserContext::GetBackgroundSyncController() {
    return NULL;
  }

  net::URLRequestContextGetter* EGLContentBrowserContext::CreateRequestContext(
    ProtocolHandlerMap* protocol_handlers,
    URLRequestInterceptorScopedVector request_interceptors) {
    url_request_context_getter_.reset(
      new EGLContentURLRequestContextGetter(
	protocol_handlers, std::move(request_interceptors),
	cache_path_, accept_language_, user_agent_));
    resource_context_->SetURLRequestContextGetter(
      url_request_context_getter_.get());
    return url_request_context_getter_.get();
  }

  net::URLRequestContextGetter* EGLContentBrowserContext::CreateRequestContextForStoragePartition(
    const base::FilePath& partition_path,
    bool in_memory,
    ProtocolHandlerMap* protocol_handlers,
    URLRequestInterceptorScopedVector request_interceptors) {
    return NULL;
  }

  net::URLRequestContextGetter* EGLContentBrowserContext::CreateMediaRequestContext() {
    return url_request_context_getter_.get();
  }

  net::URLRequestContextGetter* EGLContentBrowserContext::CreateMediaRequestContextForStoragePartition(
    const base::FilePath& partition_path,
    bool in_memory) {
    return NULL;
  }

  BackgroundFetchDelegate* EGLContentBrowserContext::GetBackgroundFetchDelegate() {
    return nullptr;
  }

  BrowsingDataRemoverDelegate*
  EGLContentBrowserContext::GetBrowsingDataRemoverDelegate() {
    return nullptr;
  }
}
