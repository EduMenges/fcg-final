#pragma once

#include "Shader.hpp"

class GPUProgram {
   public:
    GPUProgram(Shader&& vertex, Shader&& fragment);

    GPUProgram(const GPUProgram& other) = delete;

    ~GPUProgram() {
        glDeleteProgram(id_);
    }

    [[nodiscard]] constexpr GLuint GetId() const noexcept { return id_; }

   private:
    /// GPU program id
    GLuint id_{glCreateProgram()};
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
