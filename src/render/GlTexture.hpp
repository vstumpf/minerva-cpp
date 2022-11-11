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
  GLuint textureId_{0};
  GLenum bindedTarget_{0};
};

#endif  // MINERVA_RENDER_GLTEXTURE_HPP_
