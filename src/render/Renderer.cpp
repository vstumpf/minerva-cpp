#include "render/Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

#include "render/const.hpp"
#include "render/Window.hpp"

#include "common/debug.hpp"

#include <glad/glad.h>

const std::string vertexShaderSource = 
	R"glsl(
#version 330 core
in vec2 position;
in vec3 color;

out vec3 Color;

void main()
{
	Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

const std::string fragmentShaderSource = 
	R"glsl(
#version 330 core

in vec3 Color;
out vec4 outColor;

void main()
{
    outColor = vec4(Color, 1.0);
}
)glsl";

Renderer::Renderer(Window * window, PixelFormat pf) :
	window_(window),
	pf_(pf),
	vertexShader_(vertexShaderSource, GL_VERTEX_SHADER),
	fragmentShader_(fragmentShaderSource, GL_FRAGMENT_SHADER) {
	setSize(window->getWidth(), window->getHeight());
	program_.init({vertexShader_, fragmentShader_});

	std::vector<float> vertices = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
	};

	myVbo_.SetVertexFormat<float>();
	myVbo_.Bind();
	myVbo_.SetData(vertices.data(), vertices.size(), GL_STATIC_DRAW);
	myVbo_.Unbind();
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

char const* gl_error_string(GLenum const err) noexcept
{
  switch (err)
  {
    // opengl 2 errors (8)
    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";

    // opengl 3 errors (1)
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    // gles 2, 3 and gl 4 error are handled by the switch above
    default:
      assert(!"unknown error");
      return nullptr;
  }
}


void Renderer::drawScene() {

	GLLOG(debug, "start drawScene");
	program_.bind();

	GLLOG(debug, "bind vbo");
	myVbo_.Bind();

	// Setup layout of vertex data
	GLLOG(debug, "setup layout: {}", position_attrib);
	const GLuint position_attrib = program_.getAttributeLocation("position");
	glEnableVertexAttribArray(position_attrib);
	glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	const GLuint color_attrib = program_.getAttributeLocation("color");
	glEnableVertexAttribArray(color_attrib);
	glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

	GLLOG(debug, "draw triangles");
	glDrawArrays(GL_TRIANGLES, 0, 3);
	auto error = glGetError();

	GLLOG(debug, gl_error_string(error));
	GLLOG(debug, "disable layout");
	glDisableVertexAttribArray(position_attrib);
	GLLOG(debug, "unbind vbo");
	myVbo_.Unbind();
	GLLOG(debug, "unbind program");
	program_.unbind();
	GLLOG(debug, "end drawScene");
}


void Renderer::flip() {
	// LOG(debug, "start flip");
	window_->drawFrame();
	frameCount_++;
	auto current_ticks = SDL_GetTicks();
	if (current_ticks > frameTick_ + 1000) {
		LOG(debug, "FPS: {}", frameCount_);
		frameCount_ = 0;
		frameTick_ = SDL_GetTicks();
	}
	// LOG(debug, "end flip");
}

void Renderer::clear() {
	window_->clear(0xFF000000);
}