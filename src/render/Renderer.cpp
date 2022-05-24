#include "render/Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

#include "render/const.hpp"


Renderer::Renderer(uint32_t width, uint32_t height, PixelFormat pf) :
	pf_(pf) {
	setSize(width, height);

}

bool Renderer::init() {
	return true;
}

void Renderer::setSize(uint32_t width, uint32_t height) {
	width_ = width;
	height_ = height;
	
	halfWidth_ = width / 2;
	halfHeight_ = height / 2;

	aspectRatio_ = width / static_cast<float>(height);
	
	hpc_ = (static_cast<float>(width) / 2.f) /
		glm::tan(PI * 15.f * (1.f / 360.f));
	vpc_ = (static_cast<float>(height) / 2.f) /
		glm::tan(PI * 15.f * (1.f / 360.f));
	
	hratio_ = glm::tan((90.f - 15.f * 0.5f) * PI * (1.f / 180.f));
	vratio_ = glm::tan((90.f - 15.f * 0.5f) * PI * (1.f / 180.f));

	xoffset_ = width / 2.f;
	yoffset_ = height / 2.f;

	hpc_ = aspectRatio_ * hpc_;
	hratio_ = aspectRatio_ * hratio_;

	screenXFactor_ = width * (1.f / 640.f);
	screenYFactor_ = height * (1.f / 480.f);

	projectionMatrix_ = glm::perspective(
		70.f,
		width / static_cast<float>(height),
		1.f,
		2000.f);
	projectionMatrix2d_ = glm::ortho(
		0.f,
		static_cast<float>(width),
		static_cast<float>(height),
		0.f,
		-1.f,
		1.f);
}