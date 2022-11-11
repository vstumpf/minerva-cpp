#ifndef MINERVA_RENDER_SURFACE_HPP_
#define MINERVA_RENDER_SURFACE_HPP_

#include <stdint.h>

#include <SDL.h>
#include <stb_image.h>

#include "files/BmpResource.hpp"
#include "render/GlTexture.hpp"
#include "render/pixel_format.hpp"

namespace minerva::render {

class Surface : public GlTexture {
 public:
  Surface() = default;
  explicit Surface(SDL_Surface*);
  Surface(unsigned long, unsigned long);
  ~Surface();

  virtual void updateSprite(int x,
                            int y,
                            int width,
                            int height,
                            const minerva::files::BmpResource* img);

  unsigned long getWidth() const;
  unsigned long getHeight() const;
  SDL_Surface* getSDLSurface() const;

  void create(unsigned long width, unsigned long height);

 protected:
  void updateGlTexture();

 protected:
  unsigned long width_{};
  unsigned long height_{};
  SDL_Surface* sdlSurface_{nullptr};
  SDL_Surface* sdlSurfaceXflipped_{nullptr};
  bool needUpdateXflipped_{false};
};

}  // namespace minerva::render

#endif  // MINERVA_RENDER_SURFACE_HPP_
