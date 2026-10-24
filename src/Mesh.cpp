#include "Mesh.hpp"

#include <glad/glad.h>

void Mesh::render(glm::mat4 view, Shader &shader) const
{
    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f);
    shader.setUniform("projection", projection);
    shader.setUniform("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    shader.setUniform("model", model);

    shader.setUniform("color", color);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
