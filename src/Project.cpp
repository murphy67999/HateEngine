#include "Project.hpp"

#include <json.hpp>
#include <fstream>

void Project::save(const std::vector<Mesh> &meshes, const glm::vec3 &backgroundColor, const std::string &projectName)
{
    nlohmann::json j;

    j["background"] = {backgroundColor.x, backgroundColor.y, backgroundColor.z};
    j["meshes"] = nlohmann::json::array();

    for (const Mesh &mesh : meshes)
    {
        j["meshes"].push_back({{"type", mesh.type},
                               {"position", {mesh.position.x, mesh.position.y, mesh.position.z}},
                               {"scale", {mesh.scale.x, mesh.scale.y, mesh.scale.z}},
                               {"color", {mesh.color.x, mesh.color.y, mesh.color.z}}});
    }

    std::ofstream("games/" + projectName + ".hate") << j.dump(2);
}

void Project::load(std::vector<Mesh> &meshes, glm::vec3 &backgroundColor, std::string &projectName)
{
    std::ifstream file("games/" + projectName + ".hate");
    if (!file)
        return;

    nlohmann::json j;
    file >> j;

    meshes.clear();

    for (const auto &item : j["meshes"])
    {
        MeshType type = static_cast<MeshType>(item.value("type", 0));
        Mesh mesh(type);
        mesh.position = glm::vec3(item["position"][0], item["position"][1], item["position"][2]);
        mesh.scale = glm::vec3(item["scale"][0], item["scale"][1], item["scale"][2]);
        mesh.color = glm::vec3(item["color"][0], item["color"][1], item["color"][2]);

        meshes.push_back(mesh);
    }

    backgroundColor = glm::vec3(j["background"][0], j["background"][1], j["background"][2]);
}
