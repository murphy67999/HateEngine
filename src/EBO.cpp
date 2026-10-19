#include <glad/glad.h>

#include "EBO.hpp"

EBO::EBO()
{
    glGenBuffers(1, &m_EBO);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &m_EBO);
}

void EBO::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void EBO::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setData(GLsizeiptr size, const void *data, GLenum usage) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}