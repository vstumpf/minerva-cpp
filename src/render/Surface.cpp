#include "render/Surface.hpp"

#include <glad/glad.h>
#include <algorithm>
#include "common/debug.hpp"

namespace minerva::render {

Surface::Surface()
    : width_(),
      height_(),
      sdlSurface_(nullptr),
      needUpdateXflipped_(false),
      sdlSurfaceXflipped_(nullptr) {}

Surface::~Surface() {
  if (sdlSurface_)
    SDL_FreeSurface(sdlSurface_);

  if (sdlSurfaceXflipped_)
    SDL_FreeSurface(sdlSurfaceXflipped_);
}

unsigned long Surface::getWidth() const {
  return width_;
}

unsigned long Surface::getHeight() const {
  return height_;
}

SDL_Surface* Surface::getSDLSurface() const {
  return sdlSurface_;
}

void Surface::create(unsigned long width, unsigned long height) {
  width_ = width;
  height_ = height;
}

void Surface::updateSprite(int x,
                           int y,
                           int width,
                           int height,
                           const minerva::files::BmpResource* img) {
  if (sdlSurface_ && (sdlSurface_->w != width || sdlSurface_->h != height)) {
    SDL_FreeSurface(sdlSurface_);
    sdlSurface_ = nullptr;
  }

  if (!sdlSurface_) {
    create(width, height);
    sdlSurface_ = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xff,
                                       0xff00, 0xff0000, 0xff000000);
  }

  auto surfaceSize = sdlSurface_->w * sdlSurface_->h;
  uint32_t* surfaceData = static_cast<uint32_t*>(sdlSurface_->pixels);

  SDL_LockSurface(sdlSurface_);
  // for (int ax = 0; ax < width; ax++) {
  //   for (int ay = 0; ay < height; ay++) {
  //     auto idx = ax + (ay * width);
  //     LOG(info, "ax {0}, ay {1}, idx {2}", ax, ay, idx);
  //     auto color = img->getColor(ax, ay);
  //     LOG(info, "color {}", color);
  //     surfaceData[idx] = color;
  //   }
  // }

  memcpy(surfaceData, img->getData(), surfaceSize * 4);

  SDL_UnlockSurface(sdlSurface_);
  updateGlTexture();
}

void Surface::updateGlTexture() {
  bind(GL_TEXTURE_2D);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface_->w, sdlSurface_->h, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface_->pixels);

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  needUpdateXflipped_ = true;
  unbind();
}

}  // namespace minerva::render
