#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Shader {
   public:
    Shader(const Shader& other) = delete;

    ~Shader() { glDeleteShader(shader_id_); }

    [[nodiscard]] constexpr GLuint GetId() const noexcept { return shader_id_; }

   protected:
    Shader(const std::filesystem::path& filename, GLuint shader_id);
    GLuint shader_id_;
};

namespace shader {
class Vertex : public Shader {
   public:
    explicit Vertex(const std::filesystem::path& filename) : Shader(filename, glCreateShader(GL_VERTEX_SHADER)) {}
};

class Fragment : public Shader {
   public:
    explicit Fragment(const std::filesystem::path& filename) : Shader(filename, glCreateShader(GL_FRAGMENT_SHADER)) {}
};
}
