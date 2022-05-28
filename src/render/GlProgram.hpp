#ifndef MINERVA_RENDER_GLPROGRAM_HPP_
#define MINERVA_RENDER_GLPROGRAM_HPP_

#include <vector>
#include <glad/glad.h>

#include "render/GlShader.hpp"

class GlProgram {
 public:
  GlProgram();
  ~GlProgram();

  bool init(const std::vector<GlShader>& shaders);
  void bind() const;
  void unbind() const;
  GLuint getId() const;
  GLuint getUniformLocation(const std::string& uniform_name) const;
  GLuint getAttributeLocation(const std::string& attribute_name) const;

 private:
  // Disable object copy
  GlProgram(const GlProgram&);
  const GlProgram& operator=(const GlProgram&);

 private:
  GLuint program_id_;
};

#endif  // MINERVA_RENDER_GLPROGRAM_HPP_
