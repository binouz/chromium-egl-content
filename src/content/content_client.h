#ifndef EGLCONTENT_CONTENT_CONTENT_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_CLIENT_H_

#include "content/public/common/content_client.h"

#include "content/eglcontent/api/main_delegate.h"

namespace EGLContent {
  struct BrowserConfig;
};

namespace content {

  class EGLContentClient : public ContentClient {

    public:
      EGLContentClient(EGLContent::MainDelegate* delegate,
                       EGLContent::BrowserConfig& config);
      ~EGLContentClient();

      // Gives the embedder a chance to register its own pepper plugins.
      void AddPepperPlugins(
	std::vector<content::PepperPluginInfo>* plugins) override;

      // Gives the embedder a chance to register the content decryption
      // modules it supports.
      void AddContentDecryptionModules(
	std::vector<content::CdmInfo>* cdms) override;

      // Returns a string describing the embedder product name and version,
      // of the form "productname/version", with no other slashes.
      // Used as part of the user agent string.
      std::string GetProduct() const override;

      // Returns the user agent.  Content may cache this value.
      std::string GetUserAgent() const override;

      // Return the contents of a resource in a StringPiece given the resource id.
      base::StringPiece GetDataResource(
	int resource_id,
	ui::ScaleFactor scale_factor) const override;

      // Returns the raw bytes of a scale independent data resource.
      base::RefCountedMemory* GetDataResourceBytes(
	int resource_id) const override;

      // Returns a native image given its id.
      gfx::Image& GetNativeImageNamed(int resource_id) const override;

    private:

      EGLContent::MainDelegate* delegate_;

      std::string product_;
      std::string user_agent_;

  };

}

#endif /* !EGLCONTENT_CONTENT_CONTENT_CLIENT.H */
