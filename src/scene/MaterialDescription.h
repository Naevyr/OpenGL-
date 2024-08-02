#pragma once

#include <string>


struct MaterialDescription {
    std::string albedo;
    std::string normal;
    std::string roughness;
    std::string specular;
    std::string metallic;
    std::string emission;
    std::string displacement;

    std::string opacity;




    bool trasparency;



    static bool Compare(MaterialDescription material1, MaterialDescription material2);
};

