#include "GPUProgram.hpp"
#include "fmt/core.h"

GPUProgram::GPUProgram(Shader&& vertex, Shader&& fragment) { // NOLINT(*-rvalue-reference-param-not-moved)
    glAttachShader(id_, vertex.GetId());
    glAttachShader(id_, fragment.GetId());

    glLinkProgram(id_);

    GLint linked_ok = GL_FALSE;
    glGetProgramiv(id_, GL_LINK_STATUS, &linked_ok);

    // Imprime no terminal qualquer erro de linkagem
    if (linked_ok == GL_FALSE) {
        GLint log_length = 0;
        glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_length);

        std::string output(log_length + 1, '\0');

        glGetProgramInfoLog(id_, log_length, &log_length, output.data());

        fmt::println(stderr, "ERROR: OpenGL linking of program failed");
        fmt::print(stderr, "{}", output);

        throw std::runtime_error("Failure to bind shaders");
    }
}
