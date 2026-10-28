#include "Project.hpp"

#include <json.hpp>
#include <fstream>

void Project::save(const Light &light, const Environment &environment, const std::vector<Mesh> &meshes, const std::string &projectName)
{
    nlohmann::json j;

    j["environment"] = {{"backgroundColor", {environment.backgroundColor.x, environment.backgroundColor.y, environment.backgroundColor.z}},
                        {"ambientStrength", environment.ambientStrength}};

    j["light"] = {{"position", {light.pos.x, light.pos.y, light.pos.z}},
                  {"color", {light.color.x, light.color.y, light.color.z}},
                  {"specularStrength", light.specularStrength}};

    j["meshes"] = nlohmann::json::array();
    for (const Mesh &mesh : meshes)
    {
        j["meshes"].push_back({{"type", mesh.getType()},
                               {"position", {mesh.position.x, mesh.position.y, mesh.position.z}},
                               {"scale", {mesh.scale.x, mesh.scale.y, mesh.scale.z}},
                               {"color", {mesh.color.x, mesh.color.y, mesh.color.z}},
                               {"emission", {mesh.emission.x, mesh.emission.y, mesh.emission.z}}});
    }

    std::ofstream("projects/" + projectName + ".hate") << j.dump(2);
}

void Project::load(Light &light, Environment &environment, std::vector<Mesh> &meshes, std::string &projectName)
{
    std::ifstream file("projects/" + projectName + ".hate");
    if (!file)
        return;

    nlohmann::json j;
    file >> j;

    meshes.clear();

    if (j.contains("environment"))
    {
        environment.backgroundColor = glm::vec3(j["environment"]["backgroundColor"][0], j["environment"]["backgroundColor"][1], j["environment"]["backgroundColor"][2]);
        environment.ambientStrength = j["environment"]["ambientStrength"];
    }

    if (j.contains("light"))
    {
        light.pos = glm::vec3(j["light"]["position"][0], j["light"]["position"][1], j["light"]["position"][2]);
        light.color = glm::vec3(j["light"]["color"][0], j["light"]["color"][1], j["light"]["color"][2]);
        light.specularStrength = j["light"]["specularStrength"];
    }

    for (const auto &item : j["meshes"])
    {
        GeometryType type = static_cast<GeometryType>(item.value("type", 0));
        Mesh mesh(type);
        mesh.position = glm::vec3(item["position"][0], item["position"][1], item["position"][2]);
        mesh.scale = glm::vec3(item["scale"][0], item["scale"][1], item["scale"][2]);
        mesh.color = glm::vec3(item["color"][0], item["color"][1], item["color"][2]);

        if (item.contains("emission"))
        {
            mesh.emission = glm::vec3(item["emission"][0], item["emission"][1], item["emission"][2]);
        }

        meshes.push_back(mesh);
    }
}
