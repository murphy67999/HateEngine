#include "glad/glad.h"

#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &m_VAO);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void VAO::bind() const
{
    glBindVertexArray(m_VAO);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::setAttribute(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) const
{
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}