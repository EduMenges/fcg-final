#include "ObjModel.hpp"

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

    // Primeiro computamos as normais para todos os TRIÂNGULOS.
    // Segundo, computamos as normais dos VÉRTICES através do método proposto
    // por Gouraud, onde a normal de cada vértice vai ser a média das normais de
    // todas as faces que compartilham este vértice.

    size_t num_vertices = attrib_.vertices.size() / 3;

    std::vector<int>       num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0F, 0.0F, 0.0F, 0.0F));

    for (auto& shape : shapes_) {
        size_t num_triangles = shape.mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle) {
            assert(shape.mesh.num_face_vertices[triangle] == 3);

            glm::vec4 vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex) {
                tinyobj::index_t idx = shape.mesh.indices[3 * triangle + vertex];
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
                tinyobj::index_t idx = shape.mesh.indices[3 * triangle + vertex];
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
