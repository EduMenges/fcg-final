#include "Shader.hpp"

#include "fmt/core.h"

Shader::Shader(const std::filesystem::path& filename, GLuint shader_id) : shader_id_(shader_id) {
    std::ifstream file(filename);
    file.exceptions(std::ifstream::failbit);

    std::stringstream shader;
    shader << file.rdbuf();

    std::string const kAsString           = shader.str();
    const GLchar*     shader_string       = kAsString.c_str();
    const auto        kShaderStringLength = static_cast<GLint>(kAsString.length());

    glShaderSource(shader_id, 1, &shader_string, &kShaderStringLength);
    glCompileShader(shader_id);

    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    if (log_length != 0) {
        std::string output(log_length + 1, '\0');
        glGetShaderInfoLog(shader_id, log_length, &log_length, output.data());

        if (compiled_ok == GLFW_FALSE) {
            fmt::println(stderr, "ERROR: OpenGL compilation of \"{}\"", filename.string().c_str());
            throw std::runtime_error("Couldn't compile shader");
        } else {
            fmt::println("ERROR: OpenGL compilation of \"{}\"", filename.string().c_str());
        }
        fmt::print(stderr, "{}", output);
    }
}
