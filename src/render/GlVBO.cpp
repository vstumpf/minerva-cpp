#include "render/GlVBO.hpp"

#include <glad/glad.h>

GlVBO::GlVBO() {
  glGenBuffers(1, &id_);
}

GlVBO::~GlVBO() {
  if (id_ != 0) {
    glDeleteBuffers(1, &id_);
    id_ = 0;
  }
}

size_t GlVBO::size() const {
  return size_;
}

void GlVBO::setData(const void* data, size_t size, uint32_t usage) {
  size_ = size;
  glBufferData(GL_ARRAY_BUFFER, elementSize_ * size, data, usage);
}

void GlVBO::setSubData(int offset, const void* data, int size) {
  bind();
  glBufferSubData(GL_ARRAY_BUFFER, elementSize_ * offset, elementSize_ * size,
                  data);
  unbind();
}

void GlVBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void GlVBO::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
