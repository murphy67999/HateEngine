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

void Renderer::render(const Camera &camera) const
{
    glm::vec3 backgroundColor = Scene::environment.backgroundColor;
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.setUniform("ambientStrength", Scene::environment.ambientStrength);

    m_shader.setUniform("viewPos", camera.position);

    m_shader.setUniform("projection", camera.getProjectionMatrix());
    m_shader.setUniform("view", camera.getViewMatrix());

    int pointLightCount = 0;
    for (const GameObject &object : Scene::objects)
    {
        for (const PointLight &pointLight : object.pointLights)
        {
            std::string index = "[" + std::to_string(pointLightCount) + "]";
            m_shader.setUniform("pointLights" + index + ".position", pointLight.position);
            m_shader.setUniform("pointLights" + index + ".color", pointLight.color);
            m_shader.setUniform("pointLights" + index + ".intensity", pointLight.intensity);

            pointLightCount++;
        }
    }

    m_shader.setUniform("pointLightCount", pointLightCount);

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
            m_shader.setUniform("specularStrength", mesh.material.specularStrength);
            m_shader.setUniform("shininess", mesh.material.shininess);

            glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
        }
    }
}