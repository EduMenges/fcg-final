#include "ObjModel.hpp"

ObjModel::ObjModel(const std::filesystem::path& file_name, std::string_view base_dir, bool triangulate) noexcept(false) {
    fmt::println("Carregando objetos do arquivo \"{}\"", file_name.string().c_str());

    if (base_dir.empty()) {
        static std::string parent_path;
        parent_path = file_name.parent_path().generic_string();
        base_dir    = parent_path;
    }

    std::string warn;
    std::string err;
    bool        ret = tinyobj::LoadObj(
        &attrib_, &shapes_, &materials_, &warn, &err, file_name.string().c_str(), base_dir.data(), triangulate);

    if (!err.empty()) {
        fmt::println("{}", err);
    }

    if (!ret) {
        throw std::runtime_error("Erro ao carregar modelo.");
    }

    for (auto& shape : shapes_) {
        if (shape.name.empty()) {
            fmt::println(stderr,
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
