#include "render/GlProgram.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

GlProgram::GlProgram() : programId_() {}

GlProgram::~GlProgram() {
  glDeleteProgram(programId_);
}

bool GlProgram::init(const std::vector<GlShader>& shaders) {
  programId_ = glCreateProgram();
  if (programId_ == 0) {
    return false;
  }

  // Attach all the shaders
  for (const auto& shader : shaders) {
    glAttachShader(programId_, shader.id());
  }

  glBindFragDataLocation(programId_, 0, "outColor");

  // Link the shaders together
  glLinkProgram(programId_);

  // Detach all the shaders
  for (const auto& shader : shaders) {
    glDetachShader(programId_, shader.id());
  }

  GLint status;
  glGetProgramiv(programId_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    glDeleteProgram(programId_);
    programId_ = 0;
    return false;
  }

  return true;
}

void GlProgram::bind() const {
  glUseProgram(programId_);
}

void GlProgram::unbind() const {
  glUseProgram(0);
}

GLuint GlProgram::getId() const {
  return programId_;
}

GLuint GlProgram::getUniformLocation(const std::string& uniformName) const {
  return glGetUniformLocation(programId_, uniformName.c_str());
}

GLuint GlProgram::getAttributeLocation(
    const std::string& attributeName) const {
  return glGetAttribLocation(programId_, attributeName.c_str());
}

template <>
void GlProgram::setUniform<int>(const std::string& uniformName,
                                const int& val) {
  auto loc = getUniformLocation(uniformName);
  glUniform1i(loc, val);
}

template <>
void GlProgram::setUniform<float>(const std::string& uniformName,
                                  const float& val) {
  auto loc = getUniformLocation(uniformName);
  glUniform1f(loc, val);
}

template <>
void GlProgram::setUniform<bool>(const std::string& uniformName,
                                 const bool& val) {
  auto loc = getUniformLocation(uniformName);
  glUniform1i(loc, val);
}

template <>
void GlProgram::setUniform<glm::mat4>(const std::string& uniformName,
                                      const glm::mat4& val) {
  auto loc = getUniformLocation(uniformName);
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

template <>
void GlProgram::setUniform<glm::vec3>(const std::string& uniformName,
                                      const glm::vec3& val) {
  auto loc = getUniformLocation(uniformName);
  glUniform3fv(loc, 1, glm::value_ptr(val));
}

// template <>
// void GlProgram::setUniform<bool>(const std::string& uniformName, bool val) {
//   auto loc = getUniformLocation(uniformName);
//   glUniform1i(loc, val);
// }