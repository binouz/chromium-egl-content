#include "content/eglcontent/browser/resource_context.h"
#include "content/eglcontent/browser/url_request_context_getter.h"


namespace content {

  EGLContentResourceContext::EGLContentResourceContext() {
  }

  EGLContentResourceContext::~EGLContentResourceContext() {
  }

  net::HostResolver* EGLContentResourceContext::GetHostResolver() {
    return url_request_context_getter_->GetHostResolver();
  }

  net::URLRequestContext* EGLContentResourceContext::GetRequestContext() {
    return url_request_context_getter_->GetURLRequestContext();
  }

  void EGLContentResourceContext::SetURLRequestContextGetter(
    EGLContentURLRequestContextGetter* getter) {
    url_request_context_getter_ = getter;
  }

}
