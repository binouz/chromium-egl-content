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

#ifndef EGLCONTENT_BROWSER_BROWSER_CONTEXT_H_
# define EGLCONTENT_BROWSER_BROWSER_CONTEXT_H_

#include "base/files/file_path.h"

#include "content/public/browser/browser_context.h"

#include "content/eglcontent/browser/resource_context.h"
#include "content/eglcontent/browser/url_request_context_getter.h"

namespace EGLContent {
  struct BrowserConfig;
}

namespace content {

  class EGLContentBrowserContext : public BrowserContext {

    public:

      EGLContentBrowserContext(EGLContent::BrowserConfig& config);
      ~EGLContentBrowserContext();

      void Initialise();

      // Creates a delegate to initialize a HostZoomMap and persist its information.
      // This is called during creation of each StoragePartition.
      std::unique_ptr<ZoomLevelDelegate> CreateZoomLevelDelegate(
	const base::FilePath& partition_path) override;

      // Returns the path of the directory where this context's data is stored.
      base::FilePath GetPath() const override;

      // Return whether this context is incognito. Default is false.
      bool IsOffTheRecord() const override;

      // Returns the resource context.
      ResourceContext* GetResourceContext() override;

      // Returns the DownloadManagerDelegate for this context. This will be called
      // once per context. The embedder owns the delegate and is responsible for
      // ensuring that it outlives DownloadManager. It's valid to return nullptr.
      DownloadManagerDelegate* GetDownloadManagerDelegate() override;

      // Returns the guest manager for this context.
      BrowserPluginGuestManager* GetGuestManager() override;

      // Returns a special storage policy implementation, or nullptr.
      storage::SpecialStoragePolicy* GetSpecialStoragePolicy() override;

      // Returns a push messaging service. The embedder owns the service, and is
      // responsible for ensuring that it outlives RenderProcessHost. It's valid to
      // return nullptr.
      PushMessagingService* GetPushMessagingService() override;

      // Returns the SSL host state decisions for this context. The context may
      // return nullptr, implementing the default exception storage strategy.
      SSLHostStateDelegate* GetSSLHostStateDelegate() override;

      // Returns the PermissionManager associated with that context if any, nullptr
      // otherwise.
      PermissionManager* GetPermissionManager() override;

      // Returns the BackgroundSyncController associated with that context if any,
      // nullptr otherwise.
      BackgroundSyncController* GetBackgroundSyncController() override;

      // Creates the main net::URLRequestContextGetter. It's called only once.
      net::URLRequestContextGetter* CreateRequestContext(
	ProtocolHandlerMap* protocol_handlers,
	URLRequestInterceptorScopedVector request_interceptors) override;

      // Creates the net::URLRequestContextGetter for a StoragePartition. It's
      // called only once per partition_path.
      net::URLRequestContextGetter* CreateRequestContextForStoragePartition(
	const base::FilePath& partition_path,
	bool in_memory,
	ProtocolHandlerMap* protocol_handlers,
	URLRequestInterceptorScopedVector request_interceptors) override;

      // Creates the main net::URLRequestContextGetter for media resources. It's
      // called only once.
      net::URLRequestContextGetter* CreateMediaRequestContext() override;

      // Creates the media net::URLRequestContextGetter for a StoragePartition. It's
      // called only once per partition_path.
      net::URLRequestContextGetter*
      CreateMediaRequestContextForStoragePartition(
	const base::FilePath& partition_path,
	bool in_memory) override;

      // Returns the BackgroundFetchDelegate associated with that context if any,
      // nullptr otherwise
      BackgroundFetchDelegate* GetBackgroundFetchDelegate() override;

      // Returns the BrowsingDataRemoverDelegate for this context. This will be
      // called once per context. It's valid to return nullptr.
      BrowsingDataRemoverDelegate* GetBrowsingDataRemoverDelegate() override;

    private:

      base::FilePath cache_path_;
      std::string accept_language_;
      std::string user_agent_;

      std::unique_ptr<EGLContentResourceContext> resource_context_;
      std::unique_ptr<EGLContentURLRequestContextGetter> url_request_context_getter_;
  };

}

#endif /* !EGLCONTENT_BROWSER_BROWSER_CONTEXT.H */
