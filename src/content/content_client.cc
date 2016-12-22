#include "ui/base/resource/resource_bundle.h"

#include "content/eglcontent/content/content_client.h"

#include "content/eglcontent/api/browser_config.h"

namespace content {

  EGLContentClient::EGLContentClient(EGLContent::MainDelegate* delegate,
                                     EGLContent::BrowserConfig& config)
    : delegate_(delegate),
      product_(config.product_name),
      user_agent_(config.user_agent) {
  }

  EGLContentClient::~EGLContentClient() {
  }

  void EGLContentClient::AddPepperPlugins(
    std::vector<content::PepperPluginInfo>* plugins) {
    // TODO
  }

  void EGLContentClient::AddContentDecryptionModules(
    std::vector<content::CdmInfo>* cdms) {
    // TODO
  }

  std::string EGLContentClient::GetProduct() const {
    return product_;
  }

  std::string EGLContentClient::GetUserAgent() const {
    return user_agent_;
  }

  base::StringPiece EGLContentClient::GetDataResource(
    int resource_id,
    ui::ScaleFactor scale_factor) const {
    return ResourceBundle::GetSharedInstance().GetRawDataResourceForScale(
      resource_id, scale_factor);
  }

  base::RefCountedMemory* EGLContentClient::GetDataResourceBytes(
    int resource_id) const {
    return ResourceBundle::GetSharedInstance().LoadDataResourceBytes(resource_id);
  }

  gfx::Image& EGLContentClient::GetNativeImageNamed(int resource_id) const {
    return ResourceBundle::GetSharedInstance().GetNativeImageNamed(resource_id);
  }

}
