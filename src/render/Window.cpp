#include "render/Window.hpp"

#include <glad/glad.h>
#include <SDL_ttf.h>
#include "common/debug.hpp"

#include "render/pixel_format.hpp"


int Window::init(uint32_t width, uint32_t height, uint32_t msaa_samples, uint32_t dwFlags) {
	isFullscreen_ = (dwFlags & static_cast<int>(DeviceFlag::FULLSCREEN));

	const bool vsync = (dwFlags & static_cast<int>(DeviceFlag::VSYNC));
	width_ = width;
	height_ = height;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return -1;
	}

	if (TTF_Init() < 0) {
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// Multi-sampling anti-aliasing
	if (msaa_samples > 0) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	uint32_t sdlFlags = SDL_WINDOW_OPENGL;
	if (isFullscreen_) {
		sdlFlags |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE;
	}

	sdlWindow_ = SDL_CreateWindow(
		"Minerva",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width_,
		height_,
		sdlFlags);

	if (!sdlWindow_) {
		LOG(error, "Failed to create window");
		return -1;
	}

	glContext_ = SDL_GL_CreateContext(sdlWindow_);
	if (!glContext_) {
		LOG(error, "Failed to create an OpenGL context");
		return -1;
	}

	enableVsync(vsync);

	// load extensions
	if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
		return -1;
	}

	LOG(info, "Vendor:   {}", glGetString(GL_VENDOR));
	LOG(info, "Renderer: {}", glGetString(GL_RENDERER));
	LOG(info, "Version:  {}", glGetString(GL_VERSION));

	// Set the viewport
	glViewport(0, 0, width_, height_);
	if (glGetError() != GL_NO_ERROR) {
		return -1;
	}

	// glEnable(GL_DEPTH_TEST);
	// if (glGetError() != GL_NO_ERROR) {
	// 	return -1;
	// }

	// glEnable(GL_BLEND);
	// if (glGetError() != GL_NO_ERROR) {
	// 	return -1;
	// }

	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind a dummy vao to comply with core profile's specifications
	GLuint dummy_vao;
	glGenVertexArrays(1, &dummy_vao);
	glBindVertexArray(dummy_vao);

	return 0;
}

std::shared_ptr<Renderer> Window::createRenderer() {
	try {
		auto renderer = std::make_shared<Renderer>(this);
		return renderer;
	}
	catch (std::exception e) {
		LOG(error, "Failed to initialize renderer {}", e.what());
		return nullptr;
	}
}

void Window::drawFrame() {
	SDL_GL_SwapWindow(sdlWindow_);
}

void Window::enableVsync(bool enable) {
	if (enable) {
		SDL_GL_SetSwapInterval(1);
	}
	else {
		SDL_GL_SetSwapInterval(0);
	}
}

void Window::clear(uint32_t color) {
	float a, r, g, b;

	a = ((color >> 24) & 0xFF) / 255.f;
	r = ((color >> 16) & 0xFF) / 255.f;
	g = ((color >> 8) & 0xFF) / 255.f;
	b = ((color)&0xFF) / 255.f;
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
