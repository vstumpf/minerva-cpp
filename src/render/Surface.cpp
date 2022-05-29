// #include "render/surface.hpp"

// #include <glad/glad.h>
// #include <algorithm>
// #include "common/debug.hpp"

// Surface::Surface()
//     : width_(),
//       height_(),
//       sdlSurface_(nullptr),
//       needUpdateXflipped_(false),
//       sdlSurfaceXflipped_(nullptr) {}

// Surface::Surface(unsigned long w, unsigned long h) : Surface() {
//   Create(w, h);
//   sdlSurface_ = SDL_CreateRGBSurface(SDL_SWSURFACE, width_, height_, 32, 0xff,
//                                        0xff00, 0xff0000, 0xff000000);
//   UpdateGlTexture();
// }

// Surface::Surface(SDL_Surface *surface) {
//   Create(surface->w, surface->h);
//   sdlSurface_ = surface;
//   UpdateGlTexture();
// }

// Surface::~Surface() {
//   if (sdlSurface_ != nullptr) {
//     SDL_FreeSurface(sdlSurface_);
//   }

//   if (sdlSurfaceXflipped_ != nullptr) {
//     SDL_FreeSurface(sdlSurfaceXflipped_);
//   }
// }

// unsigned long Surface::GetWidth() const { return width_; }

// unsigned long Surface::GetHeight() const { return height_; }

// SDL_Surface *Surface::GetSDLSurface() const { return sdlSurface_; }

// SDL_Surface *Surface::GetSDLSurfaceXFlipped() {
//   if (sdlSurfaceXflipped_ != nullptr && !needUpdateXflipped_) {
//     return sdlSurfaceXflipped_;
//   }

//   if (sdlSurface_ == nullptr) {
//     return nullptr;
//   }

//   sdlSurfaceXflipped_ = SDL_CreateRGBSurface(
//       SDL_SWSURFACE, width_, height_, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
//   if (sdlSurfaceXflipped_ == nullptr) {
//     return nullptr;
//   }

//   const int pitch = sdlSurface_->pitch;
//   const int line_length = sdlSurface_->w;
//   auto pixels = static_cast<uint8_t *>(sdlSurface_->pixels);
//   auto rpixels = static_cast<uint8_t *>(sdlSurfaceXflipped_->pixels);

//   for (auto line = 0; line < sdlSurface_->h; ++line) {
//     std::reverse_copy(reinterpret_cast<uint32_t *>(pixels),
//                       reinterpret_cast<uint32_t *>(pixels) + line_length,
//                       reinterpret_cast<uint32_t *>(rpixels));
//     pixels += pitch;
//     rpixels += pitch;
//   }

//   return sdlSurfaceXflipped_;
// }

// void Surface::Create(unsigned long w, unsigned long h) {
//   width_ = w;
//   height_ = h;
// }

// void Surface::Update(int x, int y, int width, int height, const ILubyte *image,
//                       int drawOnlyNoTrans) {
//   if (sdlSurface_ != nullptr &&
//       (sdlSurface_->w != width || sdlSurface_->h != height)) {
//     SDL_FreeSurface(sdlSurface_);
//     sdlSurface_ = nullptr;
//   }

//   if (sdlSurface_ == nullptr) {
//     Create(width, height);
//     sdlSurface_ = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xff,
//                                          0xff00, 0xff0000, 0xff000000);
//   }

//   SDL_LockSurface(sdlSurface_);
//   memcpy(sdlSurface_->pixels, image, sdlSurface_->w * sdlSurface_->h * 4);
//   SDL_UnlockSurface(sdlSurface_);
//   UpdateGlTexture();
// }

// void Surface::CopyRect(int x, int y, int w, int h, SDL_Surface *src) {
//   if (src == nullptr || sdlSurface_ == nullptr) {
//     return;
//   }
//   SDL_Rect dst_rect;
//   dst_rect.x = x;
//   dst_rect.y = y;
//   dst_rect.w = w;
//   dst_rect.h = h;
//   SDL_BlitSurface(src, nullptr, sdlSurface_, &dst_rect);
//   UpdateGlTexture();
// }

// void Surface::BlitBitmap(int x, int y, int w, int h, const ILubyte *bitmap) {
//   if (bitmap == nullptr || sdlSurface_ == nullptr) {
//     return;
//   }

//   SDL_Surface *surface;
//   surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0xff, 0xff00,
//                                  0xff0000, 0xff000000);
//   SDL_LockSurface(surface);
//   memcpy(surface->pixels, bitmap, surface->w * surface->h * 4);
//   SDL_UnlockSurface(surface);

//   CopyRect(x, y, w, h, surface);

//   SDL_FreeSurface(surface);
// }

// void Surface::BlitSurface(int x, int y, Surface *src, int srcx, int srcy,
//                            int width, int height, int xflip, float zoomx,
//                            float zoomy) {
//   if (src == nullptr || sdlSurface_ == nullptr) {
//     return;
//   }

//   SDL_Rect src_rect, dst_rect;
//   src_rect.x = srcx;
//   src_rect.y = srcy;
//   src_rect.w = width;
//   src_rect.h = height;

//   dst_rect.x = x;
//   dst_rect.y = y;
//   dst_rect.w = static_cast<int>(width * zoomx);
//   dst_rect.h = static_cast<int>(height * zoomy);

//   SDL_Surface *sdl_surface =
//       xflip == 1 ? src->GetSDLSurfaceXFlipped() : src->GetSDLSurface();
//   SDL_BlitScaled(sdl_surface, &src_rect, sdlSurface_, &dst_rect);
//   UpdateGlTexture();
// }

// void Surface::ClearSurface(SDL_Rect *rect, uint32_t color) {
//   if (sdlSurface_ != nullptr) {
//     SDL_FillRect(sdlSurface_, rect, color);
//   }
// }

// void Surface::DrawSurface(int x, int y, int width, int height,
//                            unsigned int color) {
//   if (x + width > g_3dDevice->GetWidth()) {
//     width = g_3dDevice->GetWidth() - x;
//   }

//   if (y + height > g_3dDevice->GetHeight()) {
//     height = g_3dDevice->GetHeight() - y;
//   }

//   if (x < 0) {
//     x = 0;
//   }

//   if (y < 0) {
//     y = 0;
//   }

//   if (width > 0 && height > 0) {
//     DrawSurfaceStretch(x, y, width, height);
//   }
// }

// void Surface::DrawSurfaceStretch(int x, int y, int width, int height) {
//   g_Renderer->AddSurface({this, {x, y}, width, height});
// }

// void Surface::UpdateGlTexture() {
//   Bind(GL_TEXTURE_2D);
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface_->w, sdlSurface_->h, 0,
//                GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface_->pixels);

//   glGenerateMipmap(GL_TEXTURE_2D);

//   float largest_supported_anisotropy;
//   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
//   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
//                   largest_supported_anisotropy);

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                   GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//                   GL_LINEAR_MIPMAP_LINEAR);
//   needUpdateXflipped_ = true;
// }
