#pragma once

#include "fmt/core.h"
#include "Scene.hpp"
#include <filesystem>
#include "tiny_obj_loader.h"
#include "model/Model.hpp"

/// Estrutura que representa um modelo geométrico carregado a partir de um arquivo ".obj".
class ObjModel : Model {
   public:
    explicit ObjModel(const std::string& file_name);

    void Draw(Camera &c) override;

    glm::vec3 position_ = glm::vec3(0);
    glm::vec3 rotation_ = glm::vec3(0);
    glm::vec3 scale_ = glm::vec3(1);

    std::vector<glm::vec3> bbox_min_;
    std::vector<glm::vec3> bbox_max_;

    bool phong_ = true; // Should I render using phong_ shading?
   private:
    void ComputeNormals();

    void BuildTriangles(const std::string& base_path);

    std::vector<GLuint> vbo_ids_;
    std::vector<int> first_index_;
    std::vector<int> index_count_;
    std::vector<GLuint> texture_id_;

    tinyobj::attrib_t attrib_;
    std::vector<tinyobj::shape_t> shapes_;
    std::vector<tinyobj::material_t> materials_;
};
