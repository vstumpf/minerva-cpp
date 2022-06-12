#ifndef MINERVA_CORE_RENDERER_HPP_
#define MINERVA_CORE_RENDERER_HPP_

#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <chrono>

#include "render/Camera.hpp"
#include "render/pixel_format.hpp"
#include "render/Window.hpp"
#include "render/GlShader.hpp"
#include "render/GlProgram.hpp"
#include "render/GlVBO.hpp"
#include "files/BmpResource.hpp"

class Window; // forward declare

class Renderer {
public:
	Renderer(Window * window, PixelFormat pf = PixelFormat::A8R8G8B8);

	bool init();
	void setSize(uint32_t cx, uint32_t cy);

	void drawScene(const Camera& camera);
	void flip();
	void clear();

	glm::vec3 cameraPos{1.f};
	glm::vec3 cameraFront{1.f};
	glm::vec3 cameraUp{1.f};
	float cameraSpeed{1.05f};

private:
	Window * window_{nullptr};

	PixelFormat pf_;

	uint32_t width_{0};
	uint32_t height_{0};

	uint32_t frameCount_{0};
	uint32_t frameTick_{0};

	uint32_t halfWidth_;
	uint32_t halfHeight_;
	float aspectRatio_;
	float hpc_;
	float vpc_;
	float hratio_;
	float vratio_;
	float xoffset_;
	float yoffset_;
	float screenXFactor_;
	float screenYFactor_;
	uint32_t clearColor{ 0xFF000000 };

	glm::mat4 projectionMatrix_;
	glm::mat4 projectionMatrix2d_;

	GlShader vertexShader_;
	GlShader fragmentShader_;
	GlProgram groundProgram_;
	GlProgram spriteProgram_;
	GlVBO myVbo_;

	BmpResource image1;
	BmpResource image2;
	decltype(std::chrono::high_resolution_clock::now()) startTime_;


};

#endif /* MINERVA_CORE_WINDOW_HPP_ */