#include "Renderer.hpp"

#include <glad/glad.h>
#include "Scene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Primitives.hpp"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);

    m_shader.use();
}

void Renderer::render() const
{
    glm::vec3 backgroundColor = Scene::environment.backgroundColor;
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.setUniform("lightPos", Scene::light.position);
    m_shader.setUniform("lightColor", Scene::light.color);
    m_shader.setUniform("specularStrength", Scene::light.specularStrength);

    m_shader.setUniform("ambientStrength", Scene::environment.ambientStrength);

    m_shader.setUniform("viewPos", m_camera.getPos());

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
    m_shader.setUniform("projection", projection);
    m_shader.setUniform("view", m_camera.getLookAt());

    for (const GameObject &object : Scene::objects)
    {
        int indices = 0;

        for (const Mesh &mesh : object.meshes)
        {
            switch (mesh.getType())
            {
            case GeometryType::CUBE:
                m_cubeVAO.bind();
                indices = 36;
                break;
            case GeometryType::PYRAMID:
                m_pyramidVAO.bind();
                indices = 18;
                break;
            case GeometryType::OCTAHEDRON:
                m_octahedronVAO.bind();
                indices = 24;
                break;
            }

            glm::mat4 model(1.0f);

            model = glm::translate(model, object.transform.position);
            model = glm::rotate(model, glm::radians(object.transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(object.transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(object.transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, object.transform.scale);

            model = glm::translate(model, mesh.transform.position);
            model = glm::rotate(model, glm::radians(mesh.transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(mesh.transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(mesh.transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, mesh.transform.scale);

            m_shader.setUniform("model", model);

            m_shader.setUniform("color", mesh.material.color);
            m_shader.setUniform("emission", mesh.material.emission);

            glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
        }
    }
}

Camera *Renderer::getCamera()
{
    return &m_camera;
}
