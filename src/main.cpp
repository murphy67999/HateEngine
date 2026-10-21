#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Camera.hpp"
#include "Input.hpp"

glm::vec3 lightPos(2.0f, 1.0f, 2.0f);

int main()
{
    std::cout << "hello Hate Engine\n";

    Window window(1920, 1080, "Hate Engine");
    if (!window.isValid)
        return 1;

    glEnable(GL_DEPTH_TEST);

    Shader cubeShader("shaders/cube.vs", "shaders/cube.fs");
    Shader lightShader("shaders/light.vs", "shaders/light.fs");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

    VBO vbo;
    VAO vao;

    vbo.bind();
    vbo.setData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.bind();
    vao.setAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    vao.setAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    vbo.unbind();
    vao.unbind();

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Input input(window.getWindow(), camera);

    float lastFrame = 0.0f;

    // main loop
    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        input.process(dt);

        float orbitRadius = 2.5f;
        lightPos = glm::vec3(orbitRadius * cos(glfwGetTime()), 1.0f, orbitRadius * sin(glfwGetTime()));

        vao.bind();

        cubeShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
        cubeShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));
        glm::mat4 view = camera.getLookAt();
        cubeShader.setUniformMatrix4fv("view", glm::value_ptr(view));
        glm::mat4 model = glm::mat4(1.0f);
        cubeShader.setUniformMatrix4fv("model", glm::value_ptr(model));
        cubeShader.setUniformVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        cubeShader.setUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cubeShader.setUniformVec3("lightPos", lightPos);
        cubeShader.setUniformVec3("viewPos", camera.getPos());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightShader.use();
        lightShader.use();
        lightShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));
        lightShader.setUniformMatrix4fv("view", glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.3f));
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.update();
    }

    return 0;
}
