#pragma once

#include "Shader.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
#include "Primitives.hpp"

class Renderer
{
public:
    Renderer();
    void render(const Camera &camera) const;

private:
    Shader m_shader{"shaders/basic.vs", "shaders/basic.fs"};
    VertexArray m_cubeVAO{Primitives::cubeVertices, sizeof(Primitives::cubeVertices), Primitives::cubeIndices, sizeof(Primitives::cubeIndices)};
    VertexArray m_pyramidVAO{Primitives::pyramidVertices, sizeof(Primitives::pyramidVertices), Primitives::pyramidIndices, sizeof(Primitives::pyramidIndices)};
    VertexArray m_octahedronVAO{Primitives::octahedronVertices, sizeof(Primitives::octahedronVertices), Primitives::octahedronIndices, sizeof(Primitives::octahedronIndices)};
};