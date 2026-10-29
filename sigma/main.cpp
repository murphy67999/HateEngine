#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Project.hpp"
#include "VertexArray.hpp"
#include "Primitives.hpp"
#include "Scene.hpp"

int main()
{
    std::cout << "hello Hate Engine\n";

    // ---------------------------------------------------------------------------------------
    const float WINDOW_WIDTH = 1920.0f;
    const float WINDOW_HEIGHT = 1080.0f;
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Hate Engine");
    if (!window.isValid())
        return 1;

    glEnable(GL_DEPTH_TEST);

    // ---------------------------------------------------------------------------------------
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Input::init(window.getWindow(), &camera);

    // ---------------------------------------------------------------------------------------
    VertexArray cubeVAO(Primitives::cubeVertices, sizeof(Primitives::cubeVertices), Primitives::cubeIndices, sizeof(Primitives::cubeIndices));
    VertexArray pyramidVAO(Primitives::pyramidVertices, sizeof(Primitives::pyramidVertices), Primitives::pyramidIndices, sizeof(Primitives::pyramidIndices));
    VertexArray octahedronVAO(Primitives::octahedronVertices, sizeof(Primitives::octahedronVertices), Primitives::octahedronIndices, sizeof(Primitives::octahedronIndices));

    // ---------------------------------------------------------------------------------------
    float lastFrame = 0.0f;

    Shader shader("shaders/basic.vs", "shaders/basic.fs");
    shader.use();

    std::string projectName = "my_project";

    Project::load("sigma");
    // ---------------------------------------------------------------------------------------
    while (!window.shouldClose())
    {
        Scene::objects[0].transform.position = {sin(glfwGetTime()), 0, cos(glfwGetTime())};

        // ---------------------------------------------------------------------------------------
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ---------------------------------------------------------------------------------------
        glClearColor(Scene::environment.backgroundColor.x, Scene::environment.backgroundColor.y, Scene::environment.backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::process(dt);

        // ---------------------------------------------------------------------------------------
        shader.setUniform("lightPos", Scene::light.pos);
        shader.setUniform("lightColor", Scene::light.color);
        shader.setUniform("specularStrength", Scene::light.specularStrength);

        shader.setUniform("ambientStrength", Scene::environment.ambientStrength);

        shader.setUniform("viewPos", camera.getPos());

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
        shader.setUniform("projection", projection);
        shader.setUniform("view", camera.getLookAt());

        for (const GameObject &object : Scene::objects)
        {
            int indices = 0;

            switch (object.mesh.getType())
            {
            case GeometryType::CUBE:
                cubeVAO.bind();
                indices = 36;
                break;
            case GeometryType::PYRAMID:
                pyramidVAO.bind();
                indices = 18;
                break;
            case GeometryType::OCTAHEDRON:
                octahedronVAO.bind();
                indices = 24;
                break;
            }

            glm::mat4 model(1.0f);

            model = glm::translate(model, object.transform.position);
            model = glm::rotate(model, glm::radians(object.transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(object.transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(object.transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, object.transform.scale);

            shader.setUniform("model", model);

            shader.setUniform("color", object.material.color);
            shader.setUniform("emission", object.material.emission);

            glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
        }

        window.update();
    }
}
