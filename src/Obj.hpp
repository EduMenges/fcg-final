#pragma once

#include "fmt/core.h"
#include <filesystem>
#include <glm/vec3.hpp>
#include <optional>
#include "tiny_obj_loader.h"
#include "OpenGL.h"
#include "Camera.hpp"
#include "singleton/Collision.hpp"

class Obj {
   public:
    explicit Obj(const std::filesystem::path& file_name, bool phong = true);

    Obj(Obj&& other) = default;

    Obj(const Obj& other) = delete;

    void Draw(Camera& c, glm::mat4 model_matrix);

    std::vector<HitBox> boxes_;

    /// @c true -> Use phong shading, @c false -> Use (cursed) goraud shading
    bool phong_ = true;

   private:
    void ComputeNormals();

    void BuildTriangles(const std::filesystem::path& base_path);

    tinyobj::attrib_t                attrib_;
    std::vector<tinyobj::shape_t>    shapes_;
    std::vector<tinyobj::material_t> materials_;

    std::vector<GLuint>               vbo_ids_;
    std::vector<int>                  first_index_;
    std::vector<int>                  index_count_;
    std::vector<std::optional<GLint>> texture_id_;
    std::vector<tinyobj::material_t*> material_id_;
};
