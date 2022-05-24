#ifndef MINERVA_CORE_WINDOW_H_
#define MINERVA_CORE_WINDOW_H_

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <memory>

#include "render/Renderer.hpp"

enum class DeviceFlag : int {
	FULLSCREEN = 0x1,
	VSYNC = 0x2
};


class Window {
public: 
	Window() {};
	~Window() {
		if (sdlWindow_) 
			SDL_DestroyWindow(sdlWindow_);
		if (glContext_)
			SDL_GL_DeleteContext(glContext_);
	}

	int init(uint32_t width, uint32_t height, uint32_t msaa_samples, uint32_t flags);
	void enableVsync(bool enable);

	void drawFrame();

	std::shared_ptr<Renderer> createRenderer();

private:
	SDL_Window* sdlWindow_{ nullptr };
	SDL_GLContext glContext_{ nullptr };

	uint32_t dwRenderWidth_{ 640 };
	uint32_t dwRenderHeight_{ 480 };

	bool isFullscreen_{ false };
};

#endif /* MINERVA_CORE_WINDOW_H_ */