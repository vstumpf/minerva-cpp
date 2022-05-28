#pragma once
#ifndef MINERVA_RENDER_VBO_HPP_
#define MINERVA_RENDER_VBO_HPP_

#include <glad/glad.h>
#include <cstdint>

class GlVBO {
public:
    GlVBO();
    ~GlVBO();

    int size() const;

    template <class T>
    inline void SetVertexFormat() {
        element_size_ = sizeof(T);
    }

    void SetData(const void* data, size_t size, uint32_t usage = GL_DYNAMIC_DRAW);
    void SetSubData(int offset, const void* data, int size);
    void Bind();
    void Unbind();

private:
    size_t element_size_;
    GLuint id_;
    size_t size_;
};

#endif  // MINERVA_RENDER_VBO_HPP_
