#include "surface_manager.h"

namespace media {

  EGLContentVideoSurface* EGLContentVideoSurface::Create(
    VideoDecoderConfig& config, int id, gpu::GpuCommandBufferStub* stub) {
    gfx::NativePixmapHandle pixmap_handle;
    scoped_refptr<gl::GLImageNativePixmap> image(
      new gl::GLImageNativePixmap(config.coded_size(), GL_RGBA));
    scoped_refptr<gfx::NativePixmap> pixmap = ui::OzonePlatform::GetInstance()
      ->GetSurfaceFactoryOzone()
      ->CreateNativePixmap(
        gfx::kNullAcceleratedWidget, config.coded_size(),
        gfx::BufferFormat::BGRA_8888, pixmap_handle);
    gpu::gles2::ContextGroup* group = stub->decoder()->GetContextGroup();
    gpu::gles2::TextureManager* texture_manager = group->texture_manager();
    gpu::gles2::MailboxManager* mailbox_manager = group->mailbox_manager();
    GLuint texture_id;
    gpu::Mailbox mailbox;

    // Check that the allocation of the native buffer succeeded
    if (!pixmap->GetEGLClientBuffer()) {
      LOG(ERROR) << "Pixmap has no backing buffer";
      return NULL;
    }

    // Initialize egl image
    if (!image->Initialize(pixmap.get(), gfx::BufferFormat::BGRA_8888)) {
      LOG(ERROR) << "Failed to initialize egl image";
      return NULL;
    }

    // Create texture and bind it to the egl image
    glGenTextures(1, &texture_id);

    gfx::ScopedTextureBinder binder(GL_TEXTURE_2D, texture_id);
    scoped_refptr<gpu::gles2::TextureRef> texture_ref =
      gpu::gles2::TextureRef::Create(texture_manager, 0, texture_id);

    texture_manager->SetTarget(texture_ref.get(), GL_TEXTURE_2D);
    texture_manager->SetLevelInfo(texture_ref.get(),   // ref
                                  GL_TEXTURE_2D,       // target
                                  0,                   // level
                                  GL_RGBA,             // internal_format
                                  config.coded_size().width(),        // width
                                  config.coded_size().height(),       // height
                                  1,                   // depth
                                  0,                   // border
                                  GL_RGBA,             // format
                                  GL_UNSIGNED_BYTE,    // type
                                  gfx::Rect());        // cleared_rect
    image->BindTexImage(GL_TEXTURE_2D);
    texture_manager->SetParameteri(__func__, stub->decoder()->GetErrorState(),
                                   texture_ref.get(), GL_TEXTURE_MAG_FILTER,
                                   GL_LINEAR);
    texture_manager->SetParameteri(__func__, stub->decoder()->GetErrorState(),
                                   texture_ref.get(), GL_TEXTURE_MIN_FILTER,
                                   GL_LINEAR);

    stub->decoder()->RestoreActiveTextureUnitBinding(GL_TEXTURE_2D);

    // Create mailbox for the texture
    mailbox = gpu::Mailbox::Generate();
    mailbox_manager->ProduceTexture(mailbox, texture_ref->texture());

    return new Surface(
      mailbox_manager, pixmap, image, texture_ref, mailbox, pixmap_handle, id,
      config);
  }

  EGLContentVideoSurface::EGLContentVideoSurface(
    gpu::gles2::MailboxManager* mailbox_manager,
    scoped_refptr<gfx::NativePixmap> pixmap,
    scoped_refptr<gl::GLImageNativePixmap> image,
    scoped_refptr<gpu::gles2::TextureRef> texture_ref,
    gpu::Mailbox& mailbox,
    gfx::NativePixmapHandle pixmap_handle,
    uint32_t id,
    VideoDecoderConfig& config)
    : mailbox_manager_(mailbox_manager),
      pixmap_(pixmap),
      image_(image),
      texture_ref_(texture_ref),
      mailbox_(mailbox),
      pixmap_handle_(pixmap_handle),
      id_(id),
      coded_size_(config.coded_size()),
      visible_rect_(config.visible_rect()),
      natural_size_(config.natural_size()) {
  }

  EGLContentVideoSurface::~EGLContentVideoSurface() {
    mailbox_manager_->TextureDeleted(texture_ref_->texture());
  }

  void* EGLContentVideoSurface::GetEGLClientBuffer() {
    return pixmap->GetEGLClientBuffer();
  }

  gfx::Size EGLContentVideoSurface::CodedSize() {
    return coded_size_;
  }

  gfx::Rect EGLContentVideoSurface::VisibleRect() {
    return visible_rect_;
  }

  gfx::Size EGLContentVideoSurface::NaturalSize() {
    return natural_size_;
  }

  gpu::Mailbox& EGLContentVideoSurface::Mailbox() {
    return mailbox_;
  }

  uint32_t EGLContentVideoSurface::Id() {
    return id_;
  }

  EGLContentSurfaceManager::EGLContentSurfaceManager() {
  }

  EGLContentSurfaceManager::~EGLContentSurfaceManager() {
  }

  void EGLContentSurfaceManager::Initialise(VideoDecoderConfig& config,
                                            int max_surface_count,
                                            gpu::GpuCommandBufferStub* stub) {
    if (surfaces_.size() > 0) {
      available_surfaces_.clear();
      reserved_surfaces_.clear();
      surfaces_.clear();
    }

    for (int i = 0; i < max_surface_count; i++) {
      std::unique_ptr<EGLContentVideoSurface> surface(
	EGLContentVideoSurface::Create(config, id, stub));
      surfaces_.push_back(std::move(surface));
      available_surfaces_.push(surface.get());
    }
  }

  EGLContentVideoSurface* EGLContentSurfaceManager::GetSurface() {
    EGLContentVideoSurface* res = NULL;

    if (available_surfaces_.size() > 0) {
      res = available_surfaces_.front();
      reserved_surfaces_[res->Id()] = res;
      available_surfaces_.pop();
    }

    return res;
  }

  void EGLContentSurfaceManager::ReturnSurface(uint32_t id) {
    std::map<uint32_t, EGLContentVideoSurface*>::iterator elm =
      reserved_surfaces_.find(id);

    if (elm != reserved_surfaces_.end()) {
      available_surfaces_.push(surfaces[id].get());
      reserved_surfaces_.erase(elm);
    }
  }

}
