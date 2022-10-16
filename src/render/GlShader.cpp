#include "render/GlShader.hpp"

#include <vector>

#include "common/debug.hpp"

GlShader::GlShader(const std::string& shaderCode, GLenum shaderType) {
  // create the shader object
  shaderId_ = glCreateShader(shaderType);
  if (shaderId_ == 0) {
    throw std::runtime_error("Failed to create glShader");
  }

  // set the source code
  const char* code = shaderCode.c_str();
  glShaderSource(shaderId_, 1, (const GLchar**)&code, nullptr);
  glCompileShader(shaderId_);

  GLint status;
  glGetShaderiv(shaderId_, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(shaderId_, GL_INFO_LOG_LENGTH, &max_length);

    // max_length includes the NULL character
    std::vector<GLchar> error_log(max_length);
    glGetShaderInfoLog(shaderId_, max_length, &max_length, &error_log[0]);

    LOG(error, "Shader compilation failed:\n{}", error_log.data());

    glDeleteShader(shaderId_);
    shaderId_ = 0;
    throw std::runtime_error("Failed to create glShader");
  }
}

GlShader::~GlShader() {
  glDeleteShader(shaderId_);
}

GLuint GlShader::id() const {
  return shaderId_;
}
