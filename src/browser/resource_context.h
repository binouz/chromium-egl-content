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
