#include "GroundShader.hpp"

namespace minerva::render::shaders {

const std::string kGroundVertexShader =
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

const std::string kGroundFragmentShader =
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
	vec4 colGrowlithe1 = texture(texGrowlithe1, Texcoord);
	vec4 colGrowlithe2 = texture(texGrowlithe2, Texcoord);
	float factor = (sin(time * 3.0) + 1.0) / 2.0;
	outColor = mix(colGrowlithe1, colGrowlithe2, factor);
}
)glsl";

}