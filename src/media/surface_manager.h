#ifndef EGLCONTENT_MEDIA_SURFACE_MANAGER_H_
# define EGLCONTENT_MEDIA_SURFACE_MANAGER_H_

#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/size.h"

namespace media {

  class EGLContentVideoSurface {

    public:

      static EGLContentVideoSurface* Create(
        VideoDecoderConfig& config, int id, gpu::GpuCommandBufferStub* stub);

      ~EGLContentVideoSurface();

      void* GetEGLClientBuffer();
      gfx::Size CodedSize();
      gfx::Rect VisibleRect();
      gfx::Size NaturalSize();
      gpu::Mailbox& Mailbox();
      uint32_t Id();

    private:
      EGLContentVideoSurface(
        gpu::gles2::MailboxManager* mailbox_manager,
        scoped_refptr<gfx::NativePixmap> pixmap,
        scoped_refptr<gl::GLImageNativePixmap> image,
        scoped_refptr<gpu::gles2::TextureRef> texture_ref,
        gpu::Mailbox& mailbox,
        gfx::NativePixmapHandle pixmap_handle,
        uint32_t id,
        VideoDecoderConfig& config);

      gpu::gles2::MailboxManager* mailbox_manager_;
      scoped_refptr<gfx::NativePixmap> pixmap_;
      scoped_refptr<gl::GLImageNativePixmap> image_;
      scoped_refptr<gpu::gles2::TextureRef> texture_ref_;
      gpu::Mailbox& mailbox_;
      gfx::NativePixmapHandle pixmap_handle_;
      uint32_t id_;
      gfx::Size coded_size_;
      gfx::Rect visible_rect_;
      gfx::Size natural_size_;

  };

  class EGLContentSurfaceManager {

    public:

      EGLContentSurfaceManager();
      ~EGLContentSurfaceManager();

      void Initialise(VideoDecoderConfig& config,
                      int max_surface_count,
                      gpu::GpuCommandBufferStub* stub));
      EGLContentVideoSurface* GetSurface();
      void ReturnSurface(uint32_t id);

    private:

      std::queue<EGLContentVideoSurface*> available_surfaces_;
      std::map<uint32_t, EGLContentVideoSurface*> reserved_surfaces_;
      std::vector<std::unique_ptr<EGLContentVideoSurface> > surfaces_;

  };

}

#endif /* !EGLCONTENT_MEDIA_SURFACE_MANAGER.H */
