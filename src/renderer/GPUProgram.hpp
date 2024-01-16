#pragma once

#include "Shader.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include <glm/fwd.hpp>

class GPUProgram {
public:
    GPUProgram(Shader &&vertex, Shader &&fragment);

    GPUProgram(const GPUProgram &other) = delete;

    ~GPUProgram() {
        glDeleteProgram(id_);
    }

    [[nodiscard]] constexpr GLuint GetId() const noexcept { return id_; }

    void InsertLocation(std::string &&name);

    template<typename ...Names>
    void InsertLocation(std::string &&name, Names... names) {
        InsertLocation(std::move(name));
        InsertLocation(names...);
    }

    GLint GetUniform(const std::string& name) {
        return locations_.at(name);
    }

private:
    /// GPU program id
    GLuint id_{glCreateProgram()};

    std::unordered_map<std::string, GLint> locations_;
};
