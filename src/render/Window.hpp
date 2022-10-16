#ifndef MINERVA_CORE_WINDOW_HPP_
#define MINERVA_CORE_WINDOW_HPP_

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <memory>

#include "render/Renderer.hpp"

namespace minerva::render {

class Renderer;  // forward declare

enum class DeviceFlag : int { FULLSCREEN = 0x1, VSYNC = 0x2 };

class Window {
 public:
  Window(){};
  ~Window() {
    if (sdlWindow_)
      SDL_DestroyWindow(sdlWindow_);
    if (glContext_)
      SDL_GL_DeleteContext(glContext_);
  }

  int init(uint32_t width,
           uint32_t height,
           uint32_t msaaSamples,
           uint32_t flags);
  void enableVsync(bool enable);

  void drawFrame();

  Renderer* createRenderer();

  uint32_t getWidth() const { return width_; };
  uint32_t getHeight() const { return height_; };

  void clear(uint32_t color);

 private:
  SDL_Window* sdlWindow_{nullptr};
  SDL_GLContext glContext_{nullptr};

  uint32_t width_{640};
  uint32_t height_{480};

  bool isFullscreen_{false};
};
}  // namespace minerva::render

#endif /* MINERVA_CORE_WINDOW_HPP_ */