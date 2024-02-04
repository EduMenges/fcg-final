#pragma once

#include <numbers>
#include <optional>

#include "Shader.hpp"
#include "renderer/GPUProgram.hpp"
#include "tl/expected.hpp"
#include "Collision.hpp"

class Renderer {
public:
    static Renderer &Instance() {
        static Renderer instance;
        return instance;
    }

    /**
     * Loads a texture to the GPU.
     * @param filename Texture's file name.
     * @return Texture's id or error.
     */
    tl::expected<GLuint, std::error_code> LoadTexture(std::string filename);

    void DrawPhong(glm::mat4 model, Camera& cam, HitBox box, std::optional<GLint> texture,
                   GLuint vertex_array_id, GLenum draw_mode, GLsizei el_count, GLenum type, void *first_index);

    void DrawGouraud();

    void SetScreenRatio(float ratio) {
        perspective_ = MatrixPerspective(kFov, ratio, kNearPlane, kFarPlane);
    }

private:
    static constexpr float kFov       = std::numbers::pi_v<float> / 3.0F;
    static constexpr float kNearPlane = -0.1F;
    static constexpr float kFarPlane  = -60.0F;

    Renderer();

    GLuint loaded_textures_ = 0;

    glm::mat4 perspective_{MatrixPerspective(kFov, 1, kNearPlane, kFarPlane)};

    GPUProgram phong_;
    GPUProgram gouraud_;
};
