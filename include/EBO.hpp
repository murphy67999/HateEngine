#pragma once

class EBO{
public:
    EBO();
    ~EBO();
    void bind() const;
    void unbind() const;
    void setData(GLsizeiptr size, const void* data, GLenum usage) const;
private:
    GLuint m_EBO = 0;
};