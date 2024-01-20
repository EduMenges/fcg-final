#pragma once

#include "fmt/core.h"
#include <filesystem>
#include "tiny_obj_loader.h"
#include "Model.hpp"
#include "OpenGL.h"

namespace model {
class Obj : Model {
   public:
    explicit Obj(const std::filesystem::path& file_name, glm::vec3 position = glm::vec3(0), glm::vec3 scale = glm::vec3(1));

    void Draw(Camera& c) override;

    std::vector<glm::vec3> bbox_min_;
    std::vector<glm::vec3> bbox_max_;

    bool phong_ = true;  // Should I render using phong_ shading?
   private:
    void ComputeNormals();

    void BuildTriangles(const std::filesystem::path& base_path);

    std::vector<GLuint> vbo_ids_;
    std::vector<int>    first_index_;
    std::vector<int>    index_count_;
    std::vector<GLuint> texture_id_;

    tinyobj::attrib_t                attrib_;
    std::vector<tinyobj::shape_t>    shapes_;
    std::vector<tinyobj::material_t> materials_;
};
}
