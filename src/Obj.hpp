#pragma once

#include "fmt/core.h"
#include <filesystem>
#include <glm/vec3.hpp>
#include "tiny_obj_loader.h"
#include "OpenGL.h"
#include "Camera.hpp"

class Obj {
   public:
    struct VertexPackage {
        GLuint vbo_id;
        int    first_index;
        int    index_count;
        GLuint texture_id;
        glm::vec3 bbox_min;
        glm::vec3 bbox_max;
    };

    explicit Obj(const std::filesystem::path& file_name, glm::vec3 position = glm::vec3(0), glm::vec3 scale = glm::vec3(1));

    Obj(Obj&& other) = default;

    Obj(const Obj& other) = delete;

    void Draw(Camera& c, glm::mat4 model_matrix);

    std::vector<glm::vec3> bbox_min_;
    std::vector<glm::vec3> bbox_max_;

    bool phong_ = true;  // Should I render using phong_ shading?

   private:
    void ComputeNormals();

    void BuildTriangles(const std::filesystem::path& base_path);

    tinyobj::attrib_t                attrib_;
    std::vector<tinyobj::shape_t>    shapes_;
    std::vector<tinyobj::material_t> materials_;

    std::vector<GLuint> vbo_ids_;
    std::vector<int>    first_index_;
    std::vector<int>    index_count_;
    std::vector<GLuint> texture_id_;

    std::vector<VertexPackage> vertexes_;
};
