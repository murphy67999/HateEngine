#include <glad/glad.h>

#include "VBO.hpp"

VBO::VBO(){
    glGenBuffers(1, &m_VBO);
}

VBO::~VBO(){
    glDeleteBuffers(1, &m_VBO);
}

void VBO::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void VBO::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(GLsizeiptr size, const void* data, GLenum usage) const{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}