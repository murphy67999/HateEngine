#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <misc/cpp/imgui_stdlib.h>

#include "Shader.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Mesh.hpp"
#include "Project.hpp"
#include "Geometry.hpp"

int main()
{
    std::cout << "hello Hate Engine\n";

    // ---------------------------------------------------------------------------------------
    Window window(1600, 800, "Hate Engine");
    if (!window.isValid())
        return 1;

    glEnable(GL_DEPTH_TEST);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Input::init(window.getWindow(), &camera);

    // ---------------------------------------------------------------------------------------
    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f};

    unsigned int cubeIndices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 3, 7, 7, 4, 0,
        1, 5, 6, 6, 2, 1,
        0, 1, 5, 5, 4, 0,
        3, 2, 6, 6, 7, 3};

    float pyramidVertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.0f, 0.5f, 0.0f};

    unsigned int pyramidIndices[] = {
        0, 2, 1, 0, 3, 2,
        0, 1, 4, 1, 2, 4,
        2, 3, 4, 3, 0, 4};

    Geometry cube(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices));
    Geometry pyramid(pyramidVertices, sizeof(pyramidVertices), pyramidIndices, sizeof(pyramidIndices));

    // ---------------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    // ---------------------------------------------------------------------------------------
    float lastFrame = 0.0f;

    glm::vec3 backgroundColor(0.0f);

    std::vector<Mesh> meshes;
    Shader shader("shaders/cube.vs", "shaders/cube.fs");
    std::string projectName = "my_project";

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

        Input::process(dt);

        // ---------------------------------------------------------------------------------------
        for (const Mesh &mesh : meshes)
        {
            switch (mesh.getType())
            {
            case GeometryType::CUBE:
                cube.bind();
                mesh.update(camera.getLookAt(), shader);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                break;
            case GeometryType::PYRAMID:
                pyramid.bind();
                mesh.update(camera.getLookAt(), shader);
                glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
                break;
            }
        }

        // ---------------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("CONFIGURE");
        ImGui::Text("GPU: %s", (const char *)glGetString(GL_RENDERER));
        ImGui::Text("Vendor: %s", (const char *)glGetString(GL_VENDOR));
        ImGui::Text("FPS: %.1f", 1.0f / dt);

        ImGui::SeparatorText("Background");
        ImGui::ColorEdit3("Color", &backgroundColor.x);

        ImGui::Separator();

        if (ImGui::Button("Cube"))
        {
            meshes.emplace_back(GeometryType::CUBE);
        }

        ImGui::SameLine();

        if (ImGui::Button("Pyramid"))
        {
            meshes.emplace_back(GeometryType::PYRAMID);
        }

        ImGui::Separator();

        ImGui::InputText("Project Name", &projectName);

        if (ImGui::Button("Save"))
        {
            Project::save(meshes, backgroundColor, projectName);
        }

        if (ImGui::Button("Load"))
        {
            Project::load(meshes, backgroundColor, projectName);
        }

        for (int i = 0; i < meshes.size(); i++)
        {
            Mesh &mesh = meshes[i];

            ImGui::PushID(i);

            std::string text = "Mesh " + std::to_string(i);

            ImGui::SeparatorText(text.c_str());
            ImGui::DragFloat3("Position", &mesh.position.x, 0.1f);
            ImGui::DragFloat3("Scale", &mesh.scale.x, 0.1f);
            ImGui::ColorEdit3("Color", &mesh.color.x);
            if (ImGui::Button("Delete"))
            {
                meshes.erase(meshes.begin() + i);
            }

            ImGui::PopID();
        }

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
