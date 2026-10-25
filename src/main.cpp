#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <json.hpp>
#include <fstream>
#include <misc/cpp/imgui_stdlib.h>

#include "Shader.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Mesh.hpp"

void saveProject(const std::vector<Mesh> &meshes, const glm::vec3 &bg, const std::string &projectName)
{
    nlohmann::json j;

    j["background"] = {bg.x, bg.y, bg.z};
    j["meshes"] = nlohmann::json::array();

    for (const Mesh &mesh : meshes)
    {
        j["meshes"].push_back({{"position", {mesh.position.x, mesh.position.y, mesh.position.z}},
                               {"scale", {mesh.scale.x, mesh.scale.y, mesh.scale.z}},
                               {"color", {mesh.color.x, mesh.color.y, mesh.color.z}}});
    }

    std::ofstream("games/" + projectName + ".hate") << j.dump(2);
}

void loadProject(std::vector<Mesh> &meshes, glm::vec3 &bg, const std::string &projectName)
{
    std::ifstream file("games/" + projectName + ".hate");
    if (!file)
        return;

    nlohmann::json j;
    file >> j;

    meshes.clear();

    for (const auto &item : j["meshes"])
    {
        Mesh mesh;
        mesh.position = glm::vec3(item["position"][0], item["position"][1], item["position"][2]);
        mesh.scale = glm::vec3(item["scale"][0], item["scale"][1], item["scale"][2]);
        mesh.color = glm::vec3(item["color"][0], item["color"][1], item["color"][2]);

        meshes.push_back(mesh);
    }

    bg = glm::vec3(j["background"][0], j["background"][1], j["background"][2]);
}

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

    // ---------------------------------------------------------------------------------------
    float cubeVertices[108] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f};

    unsigned int VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        input.process(dt);

        // ---------------------------------------------------------------------------------------
        for (Mesh mesh : meshes)
        {
            glBindVertexArray(VAO);
            mesh.render(camera.getLookAt(), shader);
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

        if (ImGui::Button("Cube"))
        {
            meshes.emplace_back();
        }

        ImGui::InputText("Project Name", &projectName);

        if (ImGui::Button("Save"))
        {
            saveProject(meshes, backgroundColor, projectName);
        }

        if (ImGui::Button("Load"))
        {
            loadProject(meshes, backgroundColor, projectName);
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
