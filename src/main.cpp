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
#include "VertexArray.hpp"
#include "Primitives.hpp"
#include "Light.hpp"
#include "Environment.hpp"

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
    VertexArray cube(Primitives::cubeVertices, sizeof(Primitives::cubeVertices), Primitives::cubeIndices, sizeof(Primitives::cubeIndices));
    VertexArray pyramid(Primitives::pyramidVertices, sizeof(Primitives::pyramidVertices), Primitives::pyramidIndices, sizeof(Primitives::pyramidIndices));
    VertexArray octahedron(Primitives::octahedronVertices, sizeof(Primitives::octahedronVertices), Primitives::octahedronIndices, sizeof(Primitives::octahedronIndices));

    // ---------------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    // ---------------------------------------------------------------------------------------
    float lastFrame = 0.0f;

    std::vector<Mesh> meshes;
    Shader shader("shaders/basic.vs", "shaders/basic.fs");
    std::string projectName = "my_project";

    Light light(glm::vec3(0.0f), glm::vec3(1.0f), 0.5f);
    Environment environment(glm::vec3(0.0f), 0.5f);

    // main loop
    while (!window.shouldClose())
    {
        // ---------------------------------------------------------------------------------------
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ---------------------------------------------------------------------------------------
        glClearColor(environment.backgroundColor.x, environment.backgroundColor.y, environment.backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::process(dt);

        // ---------------------------------------------------------------------------------------
        shader.setUniform("lightPos", light.pos);
        shader.setUniform("lightColor", light.color);
        shader.setUniform("specularStrength", light.specularStrength);

        shader.setUniform("ambientStrength", environment.ambientStrength);

        shader.setUniform("view", camera.getLookAt());
        shader.setUniform("viewPos", camera.getPos());

        for (const Mesh &mesh : meshes)
        {
            switch (mesh.getType())
            {
            case GeometryType::CUBE:
                cube.bind();
                mesh.update(shader);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                break;
            case GeometryType::PYRAMID:
                pyramid.bind();
                mesh.update(shader);
                glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
                break;
            case GeometryType::OCTAHEDRON:
                octahedron.bind();
                mesh.update(shader);
                glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
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

        ImGui::SeparatorText("Light");
        ImGui::DragFloat3("Position", &light.pos.x, 0.1f);
        ImGui::ColorEdit3("Color", &light.color.x);
        ImGui::SliderFloat("Specular Strength", &light.specularStrength, 0.0f, 1.0f);

        ImGui::SeparatorText("Environment");
        ImGui::ColorEdit3("Background", &environment.backgroundColor.x);
        ImGui::SliderFloat("Ambient Strength", &environment.ambientStrength, 0.0f, 1.0f);

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

        ImGui::SameLine();

        if (ImGui::Button("Octahedron"))
        {
            meshes.emplace_back(GeometryType::OCTAHEDRON);
        }

        ImGui::Separator();

        ImGui::InputText("Project Name", &projectName);

        if (ImGui::Button("Save"))
        {
            Project::save(light, environment, meshes, projectName);
        }

        ImGui::SameLine();

        if (ImGui::Button("Load"))
        {
            Project::load(light, environment, meshes, projectName);
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
            ImGui::ColorEdit3("Emission", &mesh.emission.x);
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
