#pragma once

#include "Shader.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
#include "Primitives.hpp"

class Renderer
{
public:
    Renderer();
    void render() const;
    Camera *getCamera();

private:
    Shader m_shader{"shaders/basic.vs", "shaders/basic.fs"};
    Camera m_camera{glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
    VertexArray m_cubeVAO{Primitives::cubeVertices, sizeof(Primitives::cubeVertices), Primitives::cubeIndices, sizeof(Primitives::cubeIndices)};
    VertexArray m_pyramidVAO{Primitives::pyramidVertices, sizeof(Primitives::pyramidVertices), Primitives::pyramidIndices, sizeof(Primitives::pyramidIndices)};
    VertexArray m_octahedronVAO{Primitives::octahedronVertices, sizeof(Primitives::octahedronVertices), Primitives::octahedronIndices, sizeof(Primitives::octahedronIndices)};
};