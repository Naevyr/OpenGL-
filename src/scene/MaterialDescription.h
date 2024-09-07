#pragma once

#include <string>
#include <filesystem>

struct MaterialDescription {
    std::optional<std::filesystem::path> albedo;
    std::optional<std::filesystem::path> normal;
    std::optional<std::filesystem::path> roughness;
    std::optional<std::filesystem::path> specular;
    std::optional<std::filesystem::path> metallic;
    std::optional<std::filesystem::path> emission;
    std::optional<std::filesystem::path> displacement;

    std::optional<std::filesystem::path> opacity;




    bool trasparency;



    static bool Compare(MaterialDescription material1, MaterialDescription material2);
};

