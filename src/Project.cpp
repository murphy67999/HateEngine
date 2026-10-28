#include "Project.hpp"

#include <json.hpp>
#include <fstream>
#include <filesystem>
#include "GameObject.hpp"
#include <iostream>

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
    void save(const Scene &scene, const std::string &projectName)
    {
        nlohmann::json j;

        j["environment"] = {{"backgroundColor", vec3ToJson(scene.environment.backgroundColor)},
                            {"ambientStrength", scene.environment.ambientStrength}};

        j["light"] = {{"position", vec3ToJson(scene.light.pos)},
                      {"color", vec3ToJson(scene.light.color)},
                      {"specularStrength", scene.light.specularStrength}};

        j["objects"] = nlohmann::json::array();
        for (const GameObject &object : scene.objects)
        {
            j["objects"].push_back({{"name", object.name},
                                    {"transform", {{"position", vec3ToJson(object.transform.position)}, {"rotation", vec3ToJson(object.transform.rotation)}, {"scale", vec3ToJson(object.transform.scale)}}},
                                    {"mesh", {{"type", static_cast<int>(object.mesh.getType())}}},
                                    {"material", {{"color", vec3ToJson(object.material.color)}, {"emission", vec3ToJson(object.material.emission)}}}});
        }

        std::filesystem::create_directory("projects/" + projectName);
        std::ofstream("projects/" + projectName + "/" + projectName + ".hate") << j.dump(2);
    }

    void load(Scene &scene, const std::string &projectName)
    {
        std::ifstream file("projects/" + projectName + "/" + projectName + ".hate");
        if (!file)
            return;

        nlohmann::json j;
        file >> j;

        scene.objects.clear();

        scene.environment.backgroundColor = jsonToVec3(j["environment"]["backgroundColor"]);
        scene.environment.ambientStrength = j["environment"]["ambientStrength"];

        scene.light.pos = jsonToVec3(j["light"]["position"]);
        scene.light.color = jsonToVec3(j["light"]["color"]);
        scene.light.specularStrength = j["light"]["specularStrength"];

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

            scene.objects.push_back(object);
        }
    }
}
