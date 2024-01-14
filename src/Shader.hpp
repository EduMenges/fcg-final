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

class VertexShader : public Shader {
   public:
    explicit VertexShader(const std::filesystem::path& filename) : Shader(filename, glCreateShader(GL_VERTEX_SHADER)) {}
};

class FragmentShader : public Shader {
   public:
    explicit FragmentShader(const std::filesystem::path& filename) : Shader(filename, glCreateShader(GL_FRAGMENT_SHADER)) {}
};
