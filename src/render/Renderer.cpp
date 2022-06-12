#include "render/Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

#include "render/const.hpp"
#include "render/Window.hpp"

#include "files/BmpResource.hpp"

#include "common/debug.hpp"

#include <glad/glad.h>

const std::string vertexShaderSource = 
	R"glsl(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;
out vec2 Texcoord;

void main()
{
	Color = color;
	Texcoord = texcoord;
    gl_Position = projection * view * model * vec4(position.x, 0.0, position.y, 1.0);
}
)glsl";

const std::string fragmentShaderSource = 
	R"glsl(
#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texGrowlithe1;
uniform sampler2D texGrowlithe2;

uniform float time;

void main()
{
    // outColor = vec4(Color, 1.0);
	// outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
	vec4 colGrowlithe1 = texture(texGrowlithe1, Texcoord);
	vec4 colGrowlithe2 = texture(texGrowlithe2, Texcoord);
	float factor = (sin(time * 3.0) + 1.0) / 2.0;
	outColor = mix(colGrowlithe1, colGrowlithe2, factor);
}
)glsl";

Renderer::Renderer(Window * window, PixelFormat pf) :
	window_(window),
	pf_(pf),
	vertexShader_(vertexShaderSource, GL_VERTEX_SHADER),
	fragmentShader_(fragmentShaderSource, GL_FRAGMENT_SHADER) {
	setSize(window->getWidth(), window->getHeight());
	groundProgram_.init({vertexShader_, fragmentShader_});

	std::vector<float> vertices = {
		//  Position    Color               Texcoords
		-0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Top-left
		0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Bottom-right

		0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,  // Bottom-left
		-0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Top-left
	};

	myVbo_.SetVertexFormat<float>();
	myVbo_.Bind();
	myVbo_.SetData(vertices.data(), vertices.size(), GL_STATIC_DRAW);
	myVbo_.Unbind();

	groundTexture.Load("assets/ground/ground.bmp");

	startTime_ = std::chrono::high_resolution_clock::now();

	cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

	float yaw = -90.f, pitch = 7.f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);

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


void Renderer::drawScene(const Camera& camera) {
	auto now = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::duration<float>>(now - startTime_).count();

	GLLOG(debug, "start drawScene");
	groundProgram_.bind();

	GLLOG(debug, "bind vbo");
	myVbo_.Bind();

	// Setup layout of vertex data
	GLLOG(debug, "setup layout");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	auto model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(10.f, 0.f, 10.f));
	// model = glm::translate(model, glm::vec3(0.f, 0.f, -10.f));
	groundProgram_.setUniform("model", model);

	groundProgram_.setUniform("view", camera.GetViewMatrix());

	groundProgram_.setUniform("projection", projectionMatrix_);

	// Load texture
    GLuint textures[2];
    glGenTextures(2, textures);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, groundTexture.GetWidth(), groundTexture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, groundTexture.GetData());
	glUniform1i(groundProgram_.getUniformLocation("uTexture"), 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLLOG(debug, "draw triangles");
	glDrawArrays(GL_TRIANGLES, 0, 6);
	auto error = glGetError();

	glDeleteTextures(2, textures);

	GLLOG(debug, gl_error_string(error));
	GLLOG(debug, "disable layout");
	GLLOG(debug, "unbind vbo");
	myVbo_.Unbind();
	GLLOG(debug, "unbind program");
	groundProgram_.unbind();
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
