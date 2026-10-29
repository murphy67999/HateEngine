#include "Engine.hpp"
#include "Scene.hpp"
#include "Project.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

namespace
{
    std::string projectName;
}

void ready(Window &window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(
        "editor/assets/fonts/Inter_24pt-Medium.ttf",
        24.0f);
}

void update(float dt)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Engine Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Text("GPU: %s", (const char *)glGetString(GL_RENDERER));
    ImGui::Text("Vendor: %s", (const char *)glGetString(GL_VENDOR));
    ImGui::Text("FPS: %.1f", 1.0f / dt);
    ImGui::End();

    ImGui::Begin("Scene Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::SeparatorText("Light");
    ImGui::DragFloat3("Position", &Scene::light.position.x, 0.1f);
    ImGui::ColorEdit3("Color", &Scene::light.color.x);
    ImGui::SliderFloat("Specular Strength", &Scene::light.specularStrength, 0.0f, 1.0f);

    ImGui::SeparatorText("Environment");
    ImGui::ColorEdit3("Background", &Scene::environment.backgroundColor.x);
    ImGui::SliderFloat("Ambient Strength", &Scene::environment.ambientStrength, 0.0f, 1.0f);

    ImGui::SeparatorText("Spawn");
    if (ImGui::Button("Cube"))
    {
        Scene::objects.emplace_back("Cube", GeometryType::CUBE);
    }
    ImGui::SameLine();
    if (ImGui::Button("Pyramid"))
    {
        Scene::objects.emplace_back("Pyramid", GeometryType::PYRAMID);
    }
    ImGui::SameLine();
    if (ImGui::Button("Octahedron"))
    {
        Scene::objects.emplace_back("Octahedron", GeometryType::OCTAHEDRON);
    }

    for (int i = 0; i < Scene::objects.size(); i++)
    {
        GameObject &object = Scene::objects[i];

        ImGui::PushID(i);

        std::string text = "GameObject " + std::to_string(i);
        ImGui::SeparatorText(text.c_str());

        ImGui::DragFloat3("Position", &object.transform.position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &object.transform.rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &object.transform.scale.x, 0.1f);
        ImGui::ColorEdit3("Color", &object.material.color.x);
        ImGui::ColorEdit3("Emission", &object.material.emission.x);

        if (ImGui::Button("Delete"))
        {
            Scene::objects.erase(Scene::objects.begin() + i);
        }

        ImGui::PopID();
    }
    ImGui::End();

    ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::InputText("Project Name", &projectName);
    if (ImGui::Button("Save"))
    {
        Project::save(projectName);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        Project::load(projectName);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void end()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main()
{
    Engine engine;
    engine.run(ready, update, end, "editor");
}
