#include "Project.hpp"

#include <json.hpp>
#include <fstream>
#include <filesystem>
#include "GameObject.hpp"
#include <iostream>
#include "Scene.hpp"

namespace
{
    nlohmann::json vec3ToJson(const glm::vec3 &v)
    {
        return {v.x, v.y, v.z};
    }

    glm::vec3 jsonToVec3(const nlohmann::json &j)
    {
        return glm::vec3(j[0], j[1], j[2]);
    }
}

namespace Project
{
    void save(const std::string &projectName)
    {
        nlohmann::json j;

        j["environment"] = {{"backgroundColor", vec3ToJson(Scene::environment.backgroundColor)},
                            {"ambientStrength", Scene::environment.ambientStrength}};

        j["objects"] = nlohmann::json::array();

        for (const GameObject &object : Scene::objects)
        {
            nlohmann::json meshes = nlohmann::json::array();
            nlohmann::json pointLights = nlohmann::json::array();

            for (const Mesh &mesh : object.meshes)
            {
                meshes.push_back({{"type", mesh.getType()},
                                  {"transform", {{"position", vec3ToJson(mesh.transform.position)}, {"rotation", vec3ToJson(mesh.transform.rotation)}, {"scale", vec3ToJson(mesh.transform.scale)}}},
                                  {"color", vec3ToJson(mesh.material.color)},
                                  {"emission", vec3ToJson(mesh.material.emission)},
                                  {"specularStrength", mesh.material.specularStrength},
                                  {"shininess", mesh.material.shininess}});
            }

            for (const PointLight &pointLight : object.pointLights)
            {
                pointLights.push_back(
                    {{"position", vec3ToJson(pointLight.position)},
                     {"color", vec3ToJson(pointLight.color)},
                     {"intensity", pointLight.intensity}});
            }

            j["objects"].push_back({{"name", object.name},
                                    {"transform", {{"position", vec3ToJson(object.transform.position)}, {"rotation", vec3ToJson(object.transform.rotation)}, {"scale", vec3ToJson(object.transform.scale)}}},
                                    {"meshes", meshes},
                                    {"pointLights", pointLights}});
        }

        std::string project = "projects/" + projectName;
        std::filesystem::create_directory(project);

        if (!std::filesystem::exists(project + "/main.cpp"))
        {
            std::filesystem::copy_file(
                "templates/main.cpp",
                project + "/main.cpp");
        }
        if (!std::filesystem::exists(project + "/CMakeLists.txt"))
        {
            std::filesystem::copy_file(
                "templates/CMakeLists.txt",
                project + "/CMakeLists.txt");
        }
        std::ofstream(project + "/" + projectName + ".hate") << j.dump(2);
    }

    void load(const std::string &projectName)
    {
        std::ifstream file("projects/" + projectName + "/" + projectName + ".hate");
        if (!file)
            return;

        nlohmann::json j;
        file >> j;

        Scene::objects.clear();

        Scene::environment.backgroundColor = jsonToVec3(j["environment"]["backgroundColor"]);
        Scene::environment.ambientStrength = j["environment"]["ambientStrength"];

        for (const auto &item : j["objects"])
        {
            GameObject object(item["name"]);

            object.transform.position = jsonToVec3(item["transform"]["position"]);
            object.transform.rotation = jsonToVec3(item["transform"]["rotation"]);
            object.transform.scale = jsonToVec3(item["transform"]["scale"]);

            for (const auto &item2 : item["meshes"])
            {
                Mesh mesh(item2["type"]);

                mesh.transform.position = jsonToVec3(item2["transform"]["position"]);
                mesh.transform.rotation = jsonToVec3(item2["transform"]["rotation"]);
                mesh.transform.scale = jsonToVec3(item2["transform"]["scale"]);
                mesh.material.color = jsonToVec3(item2["color"]);
                mesh.material.emission = jsonToVec3(item2["emission"]);
                mesh.material.specularStrength = item2["specularStrength"];
                mesh.material.shininess = item2["shininess"];

                object.meshes.push_back(mesh);
            }

            for (const auto &item2 : item["pointLights"])
            {
                PointLight pointLight;

                pointLight.position = jsonToVec3(item2["position"]);
                pointLight.color = jsonToVec3(item2["color"]);
                pointLight.intensity = item2["intensity"];

                object.pointLights.push_back(pointLight);
            }

            Scene::objects.push_back(object);
        }
    }
}
