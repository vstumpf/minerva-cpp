#ifndef MINVERA_RENDER_GLSHADER_HPP_
#define MINVERA_RENDER_GLSHADER_HPP_

#include <string>

#include <glad/glad.h>

class GlShader {
 public:
  GlShader(const std::string& shaderCode, GLenum shaderType);
  ~GlShader();

  GLuint id() const;

 private:
  GLuint shaderId_;
};

#endif  // MINERVA_RENDER_GLSHADER_HPP_
