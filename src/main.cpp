#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <string>
#include <misc/cpp/imgui_stdlib.h>
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
    Window window(1600, 800, "Hate Engine");
    if (!window.isValid())
        return 1;

    glEnable(GL_DEPTH_TEST);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Input::init(window.getWindow(), &camera);

    // ---------------------------------------------------------------------------------------
    VertexArray cubeVAO(Primitives::cubeVertices, sizeof(Primitives::cubeVertices), Primitives::cubeIndices, sizeof(Primitives::cubeIndices));
    VertexArray pyramidVAO(Primitives::pyramidVertices, sizeof(Primitives::pyramidVertices), Primitives::pyramidIndices, sizeof(Primitives::pyramidIndices));
    VertexArray octahedronVAO(Primitives::octahedronVertices, sizeof(Primitives::octahedronVertices), Primitives::octahedronIndices, sizeof(Primitives::octahedronIndices));

    // ---------------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::GetStyle().ScaleAllSizes(2.0f);

    // ---------------------------------------------------------------------------------------
    float lastFrame = 0.0f;

    Shader shader("shaders/basic.vs", "shaders/basic.fs");
    shader.use();

    std::string projectName = "my_project";

    Scene scene;

    // main loop
    while (!window.shouldClose())
    {
        // ---------------------------------------------------------------------------------------
        float dt = 0.0f;
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ---------------------------------------------------------------------------------------
        glClearColor(scene.environment.backgroundColor.x, scene.environment.backgroundColor.y, scene.environment.backgroundColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::process(dt);

        // ---------------------------------------------------------------------------------------
        shader.setUniform("lightPos", scene.light.pos);
        shader.setUniform("lightColor", scene.light.color);
        shader.setUniform("specularStrength", scene.light.specularStrength);

        shader.setUniform("ambientStrength", scene.environment.ambientStrength);

        shader.setUniform("viewPos", camera.getPos());

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f);
        shader.setUniform("projection", projection);
        shader.setUniform("view", camera.getLookAt());

        for (const GameObject &object : scene.objects)
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

        // ---------------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("CONFIGURE");
        ImGui::Text("GPU: %s", (const char *)glGetString(GL_RENDERER));
        ImGui::Text("Vendor: %s", (const char *)glGetString(GL_VENDOR));
        ImGui::Text("FPS: %.1f", 1.0f / dt);

        ImGui::SeparatorText("Light");
        ImGui::DragFloat3("Position", &scene.light.pos.x, 0.1f);
        ImGui::ColorEdit3("Color", &scene.light.color.x);
        ImGui::SliderFloat("Specular Strength", &scene.light.specularStrength, 0.0f, 1.0f);

        ImGui::SeparatorText("Environment");
        ImGui::ColorEdit3("Background", &scene.environment.backgroundColor.x);
        ImGui::SliderFloat("Ambient Strength", &scene.environment.ambientStrength, 0.0f, 1.0f);

        ImGui::Separator();

        if (ImGui::Button("Cube"))
        {
            scene.objects.emplace_back("Cube", GeometryType::CUBE);
        }

        ImGui::SameLine();

        if (ImGui::Button("Pyramid"))
        {
            scene.objects.emplace_back("Pyramid", GeometryType::PYRAMID);
        }

        ImGui::SameLine();

        if (ImGui::Button("Octahedron"))
        {
            scene.objects.emplace_back("Octahedron", GeometryType::OCTAHEDRON);
        }

        ImGui::Separator();

        ImGui::InputText("Project Name", &projectName);

        if (ImGui::Button("Save"))
        {
            Project::save(scene, projectName);
        }
        ImGui::SameLine();
        if (ImGui::Button("Load"))
        {
            Project::load(scene, projectName);
        }

        for (int i = 0; i < scene.objects.size(); i++)
        {
            GameObject &object = scene.objects[i];

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
                scene.objects.erase(scene.objects.begin() + i);
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
