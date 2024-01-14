#pragma once

#include "Shader.hpp"
#include <unordered_map>

class GPUProgram {
   public:
    GPUProgram(Shader&& vertex, Shader&& fragment);

    GPUProgram(const GPUProgram& other) = delete;

    ~GPUProgram() {
        glDeleteProgram(id_);
    }

    [[nodiscard]] constexpr GLuint GetId() const noexcept { return id_; }

    void InsertLocation(std::string&& name);

    template <typename ...Names>
    void InsertLocation(std::string&& name, Names... names) {
        InsertLocation(std::move(name));
        InsertLocation(names...);
    }

   private:
    /// GPU program id
    GLuint id_{glCreateProgram()};

    std::unordered_map<std::string, GLint> locations_;

    /// Model matrix
    GLint model_uniform_{glGetUniformLocation(id_, "model")};
    /// View matrix
    GLint view_uniform_{glGetUniformLocation(id_, "view")};
    /// Projection matrix
    GLint projection_uniform_{glGetUniformLocation(id_, "projection")};
    /// Object id variable in @p fragment
    GLint object_id_uniform_{glGetUniformLocation(id_, "object_id")};
    GLint bbox_min_uniform_{glGetUniformLocation(id_, "bbox_min")};
    GLint bbox_max_uniform_{glGetUniformLocation(id_, "bbox_max")};
};
