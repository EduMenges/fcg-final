#include "Obj.hpp"

#include <utility>

#include "OpenGL.h"
#include "utils.hpp"

#include "matrices.hpp"
#include "glm/glm.hpp"
#include "SceneObject.hpp"
#include "singleton/Renderer.hpp"
#include <array>

model::Obj::Obj(const std::filesystem::path& file_name, glm::vec3 position, glm::vec3 scale) : Model(position, scale) {
    fmt::println("{}: Loading object \"{}\"", CURRENT_FUNCTION, file_name.string().c_str());

    const std::string kBasePath = file_name.parent_path().string();

    std::string warn;
    std::string err;
    bool const  kRet = tinyobj::LoadObj(&attrib_, &shapes_, &materials_, &warn, &err, file_name.string().c_str(),
                                        kBasePath.c_str(), true);

    if (!err.empty()) {
        fmt::println(stderr, "{} ERROR: {}", CURRENT_FUNCTION, err);
        throw std::runtime_error("Could not load object");
    }

    if (!warn.empty()) {
        fmt::println(stderr, "{} WARNING: {}", CURRENT_FUNCTION, warn);
    }

    if (!kRet) {
        throw std::runtime_error("Error while loading the model");
    }

    ComputeNormals();
    BuildTriangles(kBasePath);
}

void model::Obj::ComputeNormals() {
    if (!attrib_.normals.empty()) {
        return;
    }

    size_t const kNumVertices = attrib_.vertices.size() / 3;

    std::vector<int>       num_triangles_per_vertex(kNumVertices, 0);
    std::vector<glm::vec4> vertex_normals(kNumVertices, glm::vec4(0.0F, 0.0F, 0.0F, 0.0F));

    // Triangle normals computation
    for (auto& shape : shapes_) {
        size_t const kNumTriangles = shape.mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < kNumTriangles; ++triangle) {
            assert(shape.mesh.num_face_vertices[triangle] == 3);

            std::array<glm::vec4, 3> vertices{};
            for (size_t vertex = 0; vertex < vertices.size(); ++vertex) {
                tinyobj::index_t const kIdx = shape.mesh.indices[3 * triangle + vertex];
                const float            kVx  = attrib_.vertices[3 * kIdx.vertex_index + 0];
                const float            kVy  = attrib_.vertices[3 * kIdx.vertex_index + 1];
                const float            kVz  = attrib_.vertices[3 * kIdx.vertex_index + 2];
                vertices[vertex]            = glm::vec4(kVx, kVy, kVz, 1.0);
            }

            const glm::vec4 a = vertices[0];
            const glm::vec4 b = vertices[1];
            const glm::vec4 c = vertices[2];

            const glm::vec4 n = glm::normalize(CrossProduct(b - a, c - a));

            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t idx = shape.mesh.indices[3 * triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                shape.mesh.indices[3 * triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    attrib_.normals.resize(3 * kNumVertices);

    // Vertex normal computation, to be used in Gouraud shading
    for (size_t i = 0; i < vertex_normals.size(); ++i) {
        glm::vec4 n = vertex_normals[i] / static_cast<float>(num_triangles_per_vertex[i]);
        n /= Norm(n);
        attrib_.normals[3 * i + 0] = n.x;
        attrib_.normals[3 * i + 1] = n.y;
        attrib_.normals[3 * i + 2] = n.z;
    }
}

void model::Obj::BuildTriangles(const std::filesystem::path& base_path) {
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;
    std::vector<float>  normal_coefficients;
    std::vector<float>  texture_coefficients;

    constexpr float kMinval = std::numeric_limits<float>::min();
    constexpr float kMaxval = std::numeric_limits<float>::max();

    for (auto& shape : shapes_) {
        size_t       first_index   = indices.size();
        size_t const kNumTriangles = shape.mesh.num_face_vertices.size();

        uint32_t material_id = 0;

        if (!shape.mesh.material_ids.empty()) {
            material_id = shape.mesh.material_ids[0];
        }

        glm::vec3 bbox_min = glm::vec3(kMaxval, kMaxval, kMaxval);
        glm::vec3 bbox_max = glm::vec3(kMinval, kMinval, kMinval);

        for (size_t triangle = 0; triangle < kNumTriangles; ++triangle) {
            assert(shape.mesh.num_face_vertices[triangle] == 3);

            uint32_t const kLastMaterialId = std::exchange(material_id, shape.mesh.material_ids[triangle]);

            if (material_id != kLastMaterialId) {
                size_t const kLastIndex = indices.size() - 1;

                first_index_.push_back(first_index);                     // Primeiro índice
                index_count_.push_back((kLastIndex + 1) - first_index);  // Número de indices
                vbo_ids_.push_back(vertex_array_object_id);
                bbox_min_.push_back(bbox_min);
                bbox_max_.push_back(bbox_max);
                texture_id_.push_back(
                    Renderer::Instance().LoadTexture((base_path / materials_[material_id].diffuse_texname).string()).value());

                first_index = indices.size();
                bbox_min    = glm::vec3(kMaxval, kMaxval, kMaxval);
                bbox_max    = glm::vec3(kMinval, kMinval, kMinval);
            }

            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t const kIdx = shape.mesh.indices[3 * triangle + vertex];

                indices.push_back(first_index + 3 * triangle + vertex);

                const float vx = attrib_.vertices[3 * kIdx.vertex_index + 0];
                const float vy = attrib_.vertices[3 * kIdx.vertex_index + 1];
                const float vz = attrib_.vertices[3 * kIdx.vertex_index + 2];

                model_coefficients.insert(model_coefficients.end(), {vx, vy, vz, 1.0F});

                bbox_min = {std::min(bbox_min.x, vx), std::min(bbox_min.y, vy), std::min(bbox_min.z, vz)};
                bbox_max = {std::max(bbox_max.x, vx), std::max(bbox_max.y, vy), std::max(bbox_max.z, vz)};

                if (kIdx.normal_index != -1) {
                    const float nx = attrib_.normals[3 * kIdx.normal_index + 0];
                    const float ny = attrib_.normals[3 * kIdx.normal_index + 1];
                    const float nz = attrib_.normals[3 * kIdx.normal_index + 2];

                    normal_coefficients.insert(normal_coefficients.end(), {nx, ny, nz, 0.0F});
                }

                if (kIdx.texcoord_index != -1) {
                    const float u = attrib_.texcoords[2 * kIdx.texcoord_index + 0];
                    const float v = attrib_.texcoords[2 * kIdx.texcoord_index + 1];

                    texture_coefficients.push_back(u);
                    texture_coefficients.push_back(v);
                }
            }
        }

        size_t const kLastIndex = indices.size() - 1;

        first_index_.push_back(first_index);                     // Primeiro índice
        index_count_.push_back((kLastIndex + 1) - first_index);  // Número de indices
        vbo_ids_.push_back(vertex_array_object_id);
        bbox_min_.push_back(bbox_min);
        bbox_max_.push_back(bbox_max);
        texture_id_.push_back(
            Renderer::Instance().LoadTexture((base_path / materials_[material_id].diffuse_texname).string()).value());
    }

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
    GLuint location             = 0;  // "(location = 0)" em "phong_vertex.glsl"
    GLint  number_of_dimensions = 4;  // vec4 em "phong_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (!normal_coefficients.empty()) {
        GLuint VBO_normal_coefficients_id;
        glGenBuffers(1, &VBO_normal_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
        location             = 1;  // "(location = 1)" em "phong_vertex.glsl"
        number_of_dimensions = 4;  // vec4 em "phong_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if (!texture_coefficients.empty()) {
        GLuint VBO_texture_coefficients_id;
        glGenBuffers(1, &VBO_texture_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());
        location             = 2;  // "(location = 1)" em "phong_vertex.glsl"
        number_of_dimensions = 2;  // vec2 em "phong_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());

    glBindVertexArray(0);
}

void model::Obj::Draw(Camera& c) {
    glm::mat4 const kModel = MatrixTranslate(position_.x, position_.y, position_.z) *
                             MatrixScale(scale_.x, scale_.y, scale_.z) * MatrixRotateX(rotation_.x) *  //
                             MatrixRotateY(rotation_.y) *                                              //
                             MatrixRotateZ(rotation_.z);

    for (unsigned int i = 0; i < vbo_ids_.size(); i++) {
        if (phong_) {
            Renderer::Instance().DrawPhong(kModel, c, bbox_min_[i], bbox_max_[i], texture_id_[i], vbo_ids_[i],
                                           GL_TRIANGLES, index_count_[i], GL_UNSIGNED_INT,
                                           reinterpret_cast<void*>(first_index_[i] * sizeof(GLuint)));
        } else {
            //            GraphicsManager::DrawElementsGouraud(kModel, c, bbox_min_[i], bbox_max_[i],
            //                                                 texture_id_[i], vbo_ids_[i], GL_TRIANGLES,
            //                                                 index_count_[i], GL_UNSIGNED_INT,
            //                                                 reinterpret_cast<void *>(first_index_[i] *
            //                                                 sizeof(GLuint)));
        }
    }
}
