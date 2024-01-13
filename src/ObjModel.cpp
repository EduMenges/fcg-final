#include "ObjModel.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "matrices.hpp"
#include "glm/glm.hpp"

ObjModel::ObjModel(const std::filesystem::path& file_name, std::string_view base_dir,
                   bool triangulate) noexcept(false) {
    fmt::println("Carregando objetos do arquivo \"{}\"", file_name.string().c_str());

    if (base_dir.empty()) {
        static std::string parent_path;
        parent_path = file_name.parent_path().generic_string();
        base_dir    = parent_path;
    }

    std::string warn;
    std::string err;
    bool        ret = tinyobj::LoadObj(&attrib_, &shapes_, &materials_, &warn, &err, file_name.string().c_str(),
                                       base_dir.data(), triangulate);

    if (!err.empty()) {
        fmt::println("{}", err);
    }

    if (!ret) {
        throw std::runtime_error("Erro ao carregar modelo.");
    }

    for (auto& shape : shapes_) {
        if (shape.name.empty()) {
            fmt::print(stderr,
                       "*********************************************\n"
                       "Erro: Objeto sem nome dentro do arquivo '{}'.\n"
                       "Veja https://www.inf.ufrgs.br/~eslgastal/fcg-faq-etc.html#Modelos-3D-no-formato-OBJ .\n"
                       "*********************************************\n",
                       file_name.string().c_str());
            throw std::runtime_error("Objeto sem nome.");
        }
        fmt::println("- Objeto '{}'", shape.name.c_str());
    }
}

void ObjModel::ComputeNormals() {
    if (!attrib_.normals.empty()) {
        return;
    }

    size_t num_vertices = attrib_.vertices.size() / 3;

    std::vector<int>       num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0F, 0.0F, 0.0F, 0.0F));

    for (auto& shape : shapes_) {
        size_t const num_triangles = shape.mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle) {
            assert(shape.mesh.num_face_vertices[triangle] == 3);

            glm::vec4 vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t const idx = shape.mesh.indices[3 * triangle + vertex];
                const float      vx  = attrib_.vertices[3 * idx.vertex_index + 0];
                const float      vy  = attrib_.vertices[3 * idx.vertex_index + 1];
                const float      vz  = attrib_.vertices[3 * idx.vertex_index + 2];
                vertices[vertex]     = glm::vec4(vx, vy, vz, 1.0);
            }

            const glm::vec4 a = vertices[0];
            const glm::vec4 b = vertices[1];
            const glm::vec4 c = vertices[2];

            const glm::vec4 ab = a - b;
            const glm::vec4 ac = a - c;

            const glm::vec4 n = CrossProduct(ab, ac);

            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t const idx = shape.mesh.indices[3 * triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                shape.mesh.indices[3 * triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    attrib_.normals.resize(3 * num_vertices);

    for (size_t i = 0; i < vertex_normals.size(); ++i) {
        glm::vec4 n = vertex_normals[i] / static_cast<float>(num_triangles_per_vertex[i]);
        n /= Norm(n);
        attrib_.normals[3 * i + 0] = n.x;
        attrib_.normals[3 * i + 1] = n.y;
        attrib_.normals[3 * i + 2] = n.z;
    }
}

void ObjModel::BuildTrianglesAndAddToVirtualScene() {
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);
    
    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;
    std::vector<float>  normal_coefficients;
    std::vector<float>  texture_coefficients;

    for (size_t shape = 0; shape < shapes_.size(); ++shape) {
        size_t first_index   = indices.size();
        size_t num_triangles = shapes_[shape].mesh.num_face_vertices.size();

        const float minval = std::numeric_limits<float>::min();
        const float maxval = std::numeric_limits<float>::max();

        glm::vec3 bbox_min = glm::vec3(maxval, maxval, maxval);
        glm::vec3 bbox_max = glm::vec3(minval, minval, minval);

        for (size_t triangle = 0; triangle < num_triangles; ++triangle) {
            assert(shapes_[shape].mesh.num_face_vertices[triangle] == 3);

            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t idx = shapes_[shape].mesh.indices[3 * triangle + vertex];

                indices.push_back(first_index + 3 * triangle + vertex);

                const float vx = attrib_.vertices[3 * idx.vertex_index + 0];
                const float vy = attrib_.vertices[3 * idx.vertex_index + 1];
                const float vz = attrib_.vertices[3 * idx.vertex_index + 2];
                // printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
                model_coefficients.push_back(vx);    // X
                model_coefficients.push_back(vy);    // Y
                model_coefficients.push_back(vz);    // Z
                model_coefficients.push_back(1.0f);  // W

                bbox_min.x = std::min(bbox_min.x, vx);
                bbox_min.y = std::min(bbox_min.y, vy);
                bbox_min.z = std::min(bbox_min.z, vz);
                bbox_max.x = std::max(bbox_max.x, vx);
                bbox_max.y = std::max(bbox_max.y, vy);
                bbox_max.z = std::max(bbox_max.z, vz);

                // Inspecionando o código da tinyobjloader, o aluno Bernardo
                // Sulzbach (2017/1) apontou que a maneira correta de testar se
                // existem normais e coordenadas de textura no ObjModel é
                // comparando se o índice retornado é -1. Fazemos isso abaixo.

                if (idx.normal_index != -1) {
                    const float nx = attrib_.normals[3 * idx.normal_index + 0];
                    const float ny = attrib_.normals[3 * idx.normal_index + 1];
                    const float nz = attrib_.normals[3 * idx.normal_index + 2];
                    normal_coefficients.push_back(nx);    // X
                    normal_coefficients.push_back(ny);    // Y
                    normal_coefficients.push_back(nz);    // Z
                    normal_coefficients.push_back(0.0f);  // W
                }

                if (idx.texcoord_index != -1) {
                    const float u = attrib_.texcoords[2 * idx.texcoord_index + 0];
                    const float v = attrib_.texcoords[2 * idx.texcoord_index + 1];
                    texture_coefficients.push_back(u);
                    texture_coefficients.push_back(v);
                }
            }
        }

        size_t last_index = indices.size() - 1;

        SceneObject theobject;
        theobject.name           = shapes_[shape].name;
        theobject.first_index    = first_index;                   // Primeiro índice
        theobject.num_indices    = last_index - first_index + 1;  // Número de indices
        theobject.rendering_mode = GL_TRIANGLES;  // Índices correspondem ao tipo de rasterização GL_TRIANGLES.
        theobject.vertex_array_object_id = vertex_array_object_id;

        theobject.bbox_min = bbox_min;
        theobject.bbox_max = bbox_max;

        g_VirtualScene[shapes_[shape].name] = theobject;
    }

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
    GLuint location             = 0;  // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4;  // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (!normal_coefficients.empty()) {
        GLuint VBO_normal_coefficients_id;
        glGenBuffers(1, &VBO_normal_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
        location             = 1;  // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 4;  // vec4 em "shader_vertex.glsl"
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
        location             = 2;  // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 2;  // vec2 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());

    glBindVertexArray(0);
}
