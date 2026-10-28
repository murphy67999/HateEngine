#pragma once

#include <glad/glad.h>

class VertexArray
{
public:
    VertexArray(const float *vertices, GLsizeiptr verticesSize, const unsigned int *indices, GLsizeiptr indicesSize);
    ~VertexArray();
    void bind() const;

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};