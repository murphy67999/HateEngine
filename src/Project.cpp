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

        j["light"] = {{"position", vec3ToJson(Scene::light.pos)},
                      {"color", vec3ToJson(Scene::light.color)},
                      {"specularStrength", Scene::light.specularStrength}};

        j["objects"] = nlohmann::json::array();
        for (const GameObject &object : Scene::objects)
        {
            j["objects"].push_back({{"name", object.name},
                                    {"transform", {{"position", vec3ToJson(object.transform.position)}, {"rotation", vec3ToJson(object.transform.rotation)}, {"scale", vec3ToJson(object.transform.scale)}}},
                                    {"mesh", {{"type", static_cast<int>(object.mesh.getType())}}},
                                    {"material", {{"color", vec3ToJson(object.material.color)}, {"emission", vec3ToJson(object.material.emission)}}}});
        }

        std::filesystem::create_directory(projectName);
        if (!std::filesystem::exists(projectName + "/main.cpp"))
        {
            std::ofstream(projectName + "/main.cpp");
        }
        if (!std::filesystem::exists(projectName + "/CMakeLists.txt"))
        {
            std::ofstream(projectName + "/CMakeLists.txt");
        }
        std::ofstream(projectName + "/" + projectName + ".hate") << j.dump(2);
    }

    void load(const std::string &projectName)
    {
        std::ifstream file(projectName + "/" + projectName + ".hate");
        if (!file)
            return;

        nlohmann::json j;
        file >> j;

        Scene::objects.clear();

        Scene::environment.backgroundColor = jsonToVec3(j["environment"]["backgroundColor"]);
        Scene::environment.ambientStrength = j["environment"]["ambientStrength"];

        Scene::light.pos = jsonToVec3(j["light"]["position"]);
        Scene::light.color = jsonToVec3(j["light"]["color"]);
        Scene::light.specularStrength = j["light"]["specularStrength"];

        for (const auto &item : j["objects"])
        {
            std::string name = item["name"];
            GeometryType type = item["mesh"]["type"];

            GameObject object(name, type);

            object.transform.position = jsonToVec3(item["transform"]["position"]);
            object.transform.rotation = jsonToVec3(item["transform"]["rotation"]);
            object.transform.scale = jsonToVec3(item["transform"]["scale"]);

            object.material.color = jsonToVec3(item["material"]["color"]);
            object.material.emission = jsonToVec3(item["material"]["emission"]);

            Scene::objects.push_back(object);
        }
    }
}
