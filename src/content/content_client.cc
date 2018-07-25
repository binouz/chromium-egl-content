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
    std::vector<content::CdmInfo>* cdms,
    std::vector<media::CdmHostFilePath>* cdm_host_file_paths) {
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
    return ui::ResourceBundle::GetSharedInstance().GetRawDataResourceForScale(
      resource_id, scale_factor);
  }

  base::RefCountedMemory* EGLContentClient::GetDataResourceBytes(
    int resource_id) const {
    return ui::ResourceBundle::GetSharedInstance().LoadDataResourceBytes(resource_id);
  }

  gfx::Image& EGLContentClient::GetNativeImageNamed(int resource_id) const {
    return ui::ResourceBundle::GetSharedInstance().GetNativeImageNamed(resource_id);
  }

}
