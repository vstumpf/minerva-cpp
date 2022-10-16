#ifndef DOLORI_RENDER_SURFACE_H_
#define DOLORI_RENDER_SURFACE_H_

#include <stdint.h>

#include <SDL.h>
#include <stb_image.h>

#include "render/GlTexture.hpp"
#include "render/pixel_format.hpp"

class Surface : public GlTexture {
 public:
  Surface();
  explicit Surface(SDL_Surface*);
  Surface(unsigned long, unsigned long);
  ~Surface();

  virtual void ClearSurface(SDL_Rect* rect, uint32_t color);
  virtual void DrawSurface(int, int, int, int, unsigned int);
  virtual void DrawSurfaceStretch(int, int, int, int);
  virtual void Update(int, int, int, int, const ILubyte*, int);

  unsigned long GetWidth() const;
  unsigned long GetHeight() const;
  SDL_Surface* GetSDLSurface() const;
  SDL_Surface* GetSDLSurfaceXFlipped();

  void Create(unsigned long, unsigned long);
  void UpdateSprite(int x,
                    int y,
                    int width,
                    int height,
                    const SprImg* img,
                    const uint32_t* pal);
  void CopyRect(int, int, int, int, SDL_Surface*);
  void BlitBitmap(int x, int y, int w, int h, const ILubyte* bitmap);
  void BlitSurface(int x,
                   int y,
                   Surface* src,
                   int srcx,
                   int srcy,
                   int width,
                   int height,
                   int xflip,
                   float zoomx,
                   float zoomy);
  void BlitSprite(int x,
                  int y,
                  CSprRes* sprRes,
                  CMotion* curMotion,
                  uint32_t* palette);

 protected:
  void UpdateGlTexture();

 protected:
  unsigned long width_;
  unsigned long height_;
  SDL_Surface* sdlSurface_;
  bool needUpdateXflipped_;
  SDL_Surface* sdlSurfaceXflipped_;
};

#endif  // DOLORI_RENDER_SURFACE_H_
