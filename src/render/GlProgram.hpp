#ifndef MINERVA_RENDER_GLPROGRAM_HPP_
#define MINERVA_RENDER_GLPROGRAM_HPP_

#include <glad/glad.h>
#include <vector>

#include "render/GlShader.hpp"

class GlProgram {
 public:
  GlProgram();
  ~GlProgram();

  bool init(const std::vector<GlShader>& shaders);
  void bind() const;
  void unbind() const;
  GLuint getId() const;
  GLuint getUniformLocation(const std::string& uniformName) const;
  GLuint getAttributeLocation(const std::string& attributeName) const;

  template <class T>
  void setUniform(const std::string& uniformName, const T& val);

 private:
  // Disable object copy
  GlProgram(const GlProgram&);
  const GlProgram& operator=(const GlProgram&);

 private:
  GLuint programId_;
};

#endif  // MINERVA_RENDER_GLPROGRAM_HPP_
