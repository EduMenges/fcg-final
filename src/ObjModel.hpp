#pragma once

#include "fmt/core.h"
#include "Scene.hpp"
#include <filesystem>
#include <tiny_obj_loader.h>

/// Estrutura que representa um modelo geométrico carregado a partir de um arquivo ".obj".
class ObjModel {
   public:
    ObjModel(const std::filesystem::path& file_name, std::string_view base_dir = "",
             bool triangulate = true) noexcept(false);

    void ComputeNormals();

    void BuildTrianglesAndAddToVirtualScene(Scene& );

    tinyobj::attrib_t                attrib_;
    std::vector<tinyobj::shape_t>    shapes_;
    std::vector<tinyobj::material_t> materials_;
};
