#include "Engine.hpp"
#include "Scene.hpp"
#include "Project.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>
#include <iostream>
#include <glm/glm.hpp>

void ready();
void update(float dt);
void end();
void imguiUpdate(float dt);
void inputUpdate(float dt);
void cursorPosCallback(GLFWwindow *window, double xPos, double yPos);
void rotateCamera(float xOffset, float yOffset);

int main()
{
    Engine::run(ready, update, end);
}

namespace
{
    std::string projectName;
    std::string objectName;
    float cameraSpeed = 5.0f;
    bool lockCamera = false;
    float cameraSensitivity = 0.1f;
    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;
    bool firstMouse = true;
}

void ready()
{
    glfwSetCursorPosCallback(Engine::window.getWindow(), cursorPosCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Engine::window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(
        "editor/assets/fonts/Inter_24pt-Medium.ttf",
        24.0f);

    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.45f, 0.04f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.85f, 0.05f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.28f, 0.03f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 0.92f, 0.94f, 1.00f);
}

void update(float dt)
{
    imguiUpdate(dt);
    inputUpdate(dt);
}

void end()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imguiUpdate(float dt)
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

    ImGui::InputText("Object Name", &objectName);
    if (ImGui::Button("Create"))
    {
        Scene::objects.emplace_back(objectName);
    }

    for (int i = 0; i < Scene::objects.size(); i++)
    {
        GameObject &object = Scene::objects[i];

        ImGui::SeparatorText(object.name.c_str());

        ImGui::PushID(i);

        ImGui::DragFloat3("Position", &object.transform.position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &object.transform.rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &object.transform.scale.x, 0.1f);

        if (ImGui::Button("Cube"))
        {
            object.meshes.emplace_back(GeometryType::CUBE);
        }
        ImGui::SameLine();
        if (ImGui::Button("Pyramid"))
        {
            object.meshes.emplace_back(GeometryType::PYRAMID);
        }
        ImGui::SameLine();
        if (ImGui::Button("Octahedron"))
        {
            object.meshes.emplace_back(GeometryType::OCTAHEDRON);
        }

        for (int j = 0; j < object.meshes.size(); j++)
        {
            ImGui::PushID(j);

            Mesh &mesh = object.meshes[j];

            ImGui::Separator();
            ImGui::DragFloat3("Position", &mesh.transform.position.x, 0.1f);
            ImGui::DragFloat3("Rotation", &mesh.transform.rotation.x, 0.1f);
            ImGui::DragFloat3("Scale", &mesh.transform.scale.x, 0.1f);
            ImGui::ColorEdit3("Color", &mesh.material.color.x);
            ImGui::ColorEdit3("Emission", &mesh.material.emission.x);

            if (ImGui::Button("Delete"))
            {
                object.meshes.erase(object.meshes.begin() + j);
            }

            ImGui::PopID();
        }

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

void inputUpdate(float dt)
{
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Engine::window.getWindow(), true);
    }

    float finalSpeed = cameraSpeed * dt;
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        Scene::camera.position += Scene::camera.direction * finalSpeed;
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        Scene::camera.position -= Scene::camera.direction * finalSpeed;
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        Scene::camera.position -= glm::normalize(glm::cross(Scene::camera.direction, Scene::camera.up)) * finalSpeed;
    if (glfwGetKey(Engine::window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        Scene::camera.position += glm::normalize(glm::cross(Scene::camera.direction, Scene::camera.up)) * finalSpeed;

    static bool zWasPressed = false;
    bool zIsPressed = glfwGetKey(Engine::window.getWindow(), GLFW_KEY_Z) == GLFW_PRESS;
    if (zIsPressed && !zWasPressed)
    {
        lockCamera = !lockCamera;

        if (lockCamera)
        {
            firstMouse = true;
            glfwSetInputMode(Engine::window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(Engine::window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    zWasPressed = zIsPressed;
}

void cursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (!lockCamera)
        return;

    static float lastX = 0.0f;
    static float lastY = 0.0f;

    if (firstMouse)
    {
        firstMouse = false;
        lastX = xPos;
        lastY = yPos;
        return;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    rotateCamera(xOffset, yOffset);
}

void rotateCamera(float xOffset, float yOffset)
{
    cameraYaw += xOffset * cameraSensitivity;
    cameraPitch += yOffset * cameraSensitivity;

    cameraPitch = glm::clamp(cameraPitch, -89.0f, 89.0f);

    Scene::camera.direction.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    Scene::camera.direction.y = sin(glm::radians(cameraPitch));
    Scene::camera.direction.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
}