#include "SpriteShader.hpp"

namespace minerva::render::shaders {

const std::string kSpriteVertexShader =
	R"glsl(
#version 330 core
layout (location = 0) in vec2 aPosition;
layout (location = 2) in vec2 aTextureCoord;

    uniform mat4 uModelViewMat;
    uniform mat4 uProjectionMat;

    uniform float uCameraLatitude;

    out vec2 Texcoord;

	// these are uniforms, but make them here because we don't support them yet
	vec3 uSpriteRendererPosition = vec3(0.f, 0.f, 0.f);
	vec2 uSpriteRendererSize = vec2(1.0f, 1.0f);
	// uSpriteRendererSize = vec2(314.f / 35.f, 277.f / 35.f - 0.f);
	vec2 uSpriteRendererOffset = vec2(0.f, 0.f);
	// uSpriteRendererOffset = vec2(0.f, -2.f);
	mat4 uSpriteRendererAngle = mat4(1.f);

	float uSpriteRendererDepth = 0.f;
	float uSpriteRendererZindex = 1;

    mat4 Project(mat4 mat, vec3 pos) {
        // xyz = x(-z)y + middle of cell (0.5)
        float x =  pos.x + 0.5;
        float y = -pos.z;
        float z =  pos.y + 0.5;

        // Matrix translation
        mat[3].x += mat[0].x * x + mat[1].x * y + mat[2].x * z;
        mat[3].y += mat[0].y * x + mat[1].y * y + mat[2].y * z;
        mat[3].z += (mat[0].z * x + mat[1].z * y + mat[2].z * z) + (uCameraLatitude / 50.0);
        mat[3].w += mat[0].w * x + mat[1].w * y + mat[2].w * z;

        // Spherical billboard
        mat[0].xyz = vec3(1.0, 0.0, 0.0);
        mat[1].xyz = vec3(0.0, 1.0 + 0.5 / uCameraLatitude, uCameraLatitude / 50.0);
        mat[2].xyz = vec3(0.0, 0.0, 1.0);

        return mat;
    }

    void main(void) {
        Texcoord = aTextureCoord;

        // Calculate position base on angle and sprite offset/size
        vec4 position = uSpriteRendererAngle * vec4(aPosition.x * uSpriteRendererSize.x, aPosition.y * uSpriteRendererSize.y, 0.0, 1.0);
        position.x   += uSpriteRendererOffset.x;
        position.y   -= uSpriteRendererOffset.y + 0.5;

        // Project to camera plane
        gl_Position   = uProjectionMat * Project(uModelViewMat, uSpriteRendererPosition) * position;
        gl_Position.z -= uSpriteRendererZindex * 0.01 + uSpriteRendererDepth;
}
)glsl";

const std::string kSpriteFragmentShader =
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