#include "render/GlProgram.hpp"

#include <glad/glad.h>

GlProgram::GlProgram() : program_id_() {}

GlProgram::~GlProgram() { glDeleteProgram(program_id_); }

bool GlProgram::init(const std::vector<GlShader>& shaders) {
  program_id_ = glCreateProgram();
  if (program_id_ == 0) {
    return false;
  }

  // Attach all the shaders
  for (const auto& shader : shaders) {
    glAttachShader(program_id_, shader.id());
  }

	glBindFragDataLocation(program_id_, 0, "outColor");

  // Link the shaders together
  glLinkProgram(program_id_);

  // Detach all the shaders
  for (const auto& shader : shaders) {
    glDetachShader(program_id_, shader.id());
  }

  GLint status;
  glGetProgramiv(program_id_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    glDeleteProgram(program_id_);
    program_id_ = 0;
    return false;
  }

  return true;
}

void GlProgram::bind() const { glUseProgram(program_id_); }

void GlProgram::unbind() const { glUseProgram(0); }

GLuint GlProgram::getId() const { return program_id_; }

GLuint GlProgram::getUniformLocation(const std::string& uniform_name) const {
  return glGetUniformLocation(program_id_, uniform_name.c_str());
}

GLuint GlProgram::getAttributeLocation(
    const std::string& attribute_name) const {
  return glGetAttribLocation(program_id_, attribute_name.c_str());
}
