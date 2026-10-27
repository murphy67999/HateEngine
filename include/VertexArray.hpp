#pragma once

#include <glad/glad.h>

class VertexArray
{
public:
    VertexArray(float *vertices, GLsizeiptr verticesSize, unsigned int *indices, GLsizeiptr indicesSize);
    ~VertexArray();
    void bind() const;

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};