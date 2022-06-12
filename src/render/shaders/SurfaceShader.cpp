#include "GroundShader.hpp"

namespace minerva::render::shaders {

const std::string kSurfaceVertexShader =
	R"glsl(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 2) in vec2 texcoord;

uniform mat4 projection;

out vec2 Texcoord;

void main()
{
	Texcoord = texcoord;
	gl_Position = projection * vec4(position.x, position.y, 0.0, 1.0);
}
)glsl";

const std::string kSurfaceFragmentShader =
	R"glsl(
#version 330 core

in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D utexture;

void main()
{
	outColor = texture(utexture, Texcoord);
}
)glsl";

}