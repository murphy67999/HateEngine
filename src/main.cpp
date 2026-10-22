#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Shader.hpp"
#include "Window.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Camera.hpp"
#include "Input.hpp"

int main()
{
    std::cout << "hello Hate Engine\n";

    Window window(1600, 800, "Hate Engine");
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    glm::vec3 lightPos(1.5f, 0.0f, 0.0f);
    glm::vec3 lightColor(1.0f);
    glm::vec3 objectColors[] = {
        glm::vec3(1.0f, 0.2f, 0.2f),
        glm::vec3(0.2f, 0.8f, 0.4f),
        glm::vec3(0.2f, 0.4f, 1.0f),
        glm::vec3(1.0f, 0.7f, 0.1f),
        glm::vec3(0.7f, 0.2f, 0.9f)};

    glm::vec3 backgroundColor(0.0f);

    // main loop
    while (!window.shouldClose())
    {
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input.process(dt);

        vao.bind();

        cubeShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f);
        cubeShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));
        glm::mat4 view = camera.getLookAt();
        cubeShader.setUniformMatrix4fv("view", glm::value_ptr(view));
        cubeShader.setUniformVec3("lightColor", lightColor);
        cubeShader.setUniformVec3("lightPos", lightPos);
        cubeShader.setUniformVec3("viewPos", camera.getPos());
        for (int i = 0; i < 5; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            float spacing = 1.5f;
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f + i * spacing));
            cubeShader.setUniformMatrix4fv("model", glm::value_ptr(model));
            cubeShader.setUniformVec3("objectColor", objectColors[i]);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        lightShader.use();
        lightShader.use();
        lightShader.setUniformMatrix4fv("projection", glm::value_ptr(projection));
        lightShader.setUniformMatrix4fv("view", glm::value_ptr(view));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.4f));
        lightShader.setUniformMatrix4fv("model", glm::value_ptr(model));
        lightShader.setUniformVec3("lightColor", lightColor);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("CONFIGURE");
        ImGui::Text("GPU: %s", (const char *)glGetString(GL_RENDERER));
        ImGui::Text("Vendor: %s", (const char *)glGetString(GL_VENDOR));
        ImGui::Text("FPS: %.1f", 1.0f / dt);
        ImGui::Separator();
        ImGui::DragFloat3("Light Position", &lightPos.x, 0.05f);
        ImGui::ColorEdit3("Light Color", &lightColor.x);
        ImGui::Separator();
        ImGui::ColorEdit3("Background Color", &backgroundColor.x);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.update();
    }

    return 0;
}
