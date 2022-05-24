#pragma once
#ifndef MINERVA_CORE_RENDERER_H_
#define MINERVA_CORE_RENDERER_H_

#include <cstdint>
#include <glm/glm.hpp>

#include "render/pixel_format.hpp"

class Renderer {
public:
	Renderer(uint32_t width, uint32_t height, PixelFormat pf = PixelFormat::A8R8G8B8);

	bool init();
	void setSize(uint32_t cx, uint32_t cy);

private:
	PixelFormat pf_;

	uint32_t width_;
	uint32_t height_;
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
};

#endif /* MINERVA_CORE_WINDOW_H_ */