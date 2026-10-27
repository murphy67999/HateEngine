#pragma once

#include <glad/glad.h>

class Geometry
{
public:
    Geometry(float *vertices, GLsizeiptr verticesSize, unsigned int *indices, GLsizeiptr indicesSize);
    ~Geometry();
    void bind() const;

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};