#include "Mesh.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(GeometryType type) : m_type(type) {};

void Mesh::update(const Shader &shader) const
{
    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f);
    shader.setUniform("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader.setUniform("model", model);

    shader.setUniform("color", color);
}

GeometryType Mesh::getType() const
{
    return m_type;
}