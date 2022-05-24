#ifndef MINVERA_RENDER_GLSHADER_H_
#define MINVERA_RENDER_GLSHADER_H_

#include <string>

#include <glad/glad.h>

class GlShader {
public:
	GlShader(const std::string& shader_code, GLenum shader_type);
	~GlShader();

	GLuint id() const;

private:
	GLuint shader_id_;
};

#endif  // MINERVA_RENDER_GLSHADER_H_
