#ifndef MINERVA_RENDER_GLTEXTURE_HPP_
#define MINERVA_RENDER_GLTEXTURE_HPP_

#include <glad/glad.h>

class GlTexture {
 public:
  GlTexture();
  virtual ~GlTexture();

  void bind(GLenum target);
  void unbind();

  GLuint texture_id() const;

 private:
  GLuint texture_id_;
  GLenum binded_target_;
};

#endif  // MINERVA_RENDER_GLTEXTURE_HPP_
