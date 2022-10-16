#ifndef MINERVA_RENDER_GLTEXTURE_HPP_
#define MINERVA_RENDER_GLTEXTURE_HPP_

#include <glad/glad.h>

class GlTexture {
 public:
  GlTexture();
  virtual ~GlTexture();

  void bind(GLenum target);
  void unbind();

  GLuint getTextureId() const;

 private:
  GLuint textureId_;
  GLenum bindedTarget_;
};

#endif  // MINERVA_RENDER_GLTEXTURE_HPP_
