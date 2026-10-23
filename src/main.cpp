#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Camera.hpp"
#include "Input.hpp"

int main()
{
    std::cout << "hello Hate Engine\n";

    // ---------------------------------------------------------------------------------------
    Window window(1600, 800, "Hate Engine");
    if (!window.isValid)
        return 1;

    glEnable(GL_DEPTH_TEST);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Input input(window.getWindow(), camera);

    Shader cubeShader("shaders/cube.vs", "shaders/cube.fs");
    Shader lightShader("shaders/light.vs", "shaders/light.fs");

    // ---------------------------------------------------------------------------------------
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

    // ---------------------------------------------------------------------------------------
    VBO vbo;
    VAO vao;

    vbo.bind();
    vbo.setData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.bind();
    vao.setAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    vao.setAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    vbo.unbind();
    vao.unbind();

    // ---------------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    // ---------------------------------------------------------------------------------------
    float lastFrame = 0.0f;

    glm::vec3 cubePos(0.0f, 0.0f, 0.0f);
    glm::vec3 cubeColor(1.0f);
    float shininess = 32.0f;

    glm::vec3 lightPos(1.5f, 0.0f, 0.0f);
    glm::vec3 lightColor(1.0f);

    glm::vec3 backgroundColor(0.0f);

    // main loop
    while (!window.shouldClose())
    {
        // ---------------------------------------------------------------------------------------
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ---------------------------------------------------------------------------------------
        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input.process(dt);

        vao.bind();

        // ---------------------------------------------------------------------------------------
        cubeShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f);
        cubeShader.setUniform("projection", projection);
        glm::mat4 view = camera.getLookAt();
        cubeShader.setUniform("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        cubeShader.setUniform("model", model);

        cubeShader.setUniform("objectColor", cubeColor);
        cubeShader.setUniform("lightColor", lightColor);
        cubeShader.setUniform("lightPos", lightPos);
        cubeShader.setUniform("viewPos", camera.getPos());
        cubeShader.setUniform("shininess", shininess);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ---------------------------------------------------------------------------------------
        lightShader.use();

        lightShader.setUniform("projection", projection);
        lightShader.setUniform("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.5f));
        lightShader.setUniform("model", model);

        lightShader.setUniform("lightColor", lightColor);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ---------------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("CONFIGURE");
        ImGui::Text("GPU: %s", (const char *)glGetString(GL_RENDERER));
        ImGui::Text("Vendor: %s", (const char *)glGetString(GL_VENDOR));
        ImGui::Text("FPS: %.1f", 1.0f / dt);

        ImGui::SeparatorText("Cube");
        ImGui::PushID("Cube");
        ImGui::DragFloat3("Position", &cubePos.x, 0.05f);
        ImGui::ColorEdit3("Color", &cubeColor.x);
        ImGui::SliderFloat("Shininess", &shininess, 1.0f, 256.0f);
        ImGui::PopID();

        ImGui::SeparatorText("Light");
        ImGui::PushID("Light");
        ImGui::DragFloat3("Position", &lightPos.x, 0.05f);
        ImGui::ColorEdit3("Color", &lightColor.x);
        ImGui::PopID();

        ImGui::SeparatorText("Environment");
        ImGui::ColorEdit3("Background Color", &backgroundColor.x);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // ---------------------------------------------------------------------------------------
        window.update();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
