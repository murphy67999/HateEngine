#pragma once

class VAO{
public:
    VAO();
    ~VAO();
    void bind() const;
    void unbind() const;
    void setAttribute(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) const;
private:
    GLuint m_VAO = 0;
};