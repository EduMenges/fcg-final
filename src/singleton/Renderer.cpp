#include "Renderer.hpp"
#include "stb/stb_image.h"
#include "fmt/core.h"
#include "glm/gtc/type_ptr.hpp"
#include "utils.hpp"

Renderer::Renderer()
    : phong_(shader::Vertex("../../../shader/phong_vertex.glsl"),
             shader::Fragment("../../../shader/phong_fragment.glsl")),
      gouraud_(shader::Vertex("../../../shader/gouraud_vertex.glsl"),
               shader::Fragment("../../../shader/gouraud_fragment.glsl")) {
    phong_.InsertLocation("model", "view", "projection", "view_vec", "bbox_min", "bbox_max", "color_texture");
    gouraud_.InsertLocation("model", "view", "projection", "view_vec", "color_texture");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

tl::expected<GLuint, std::error_code> Renderer::LoadTexture(std::string filename) {
    fmt::println("{}: loading texture {}", CURRENT_FUNCTION, filename);

    stbi_set_flip_vertically_on_load(GLFW_TRUE);
    int            width;
    int            height;
    int            channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (data == nullptr) {
        auto error = static_cast<std::errc>(errno);
        fmt::println(stderr, "{} ERROR: cannot open texture", CURRENT_FUNCTION);
        return tl::make_unexpected(std::make_error_code(error));
    }

    fmt::println("{} SUCCESS: {} x {}", CURRENT_FUNCTION, width, height);

    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint textureunit = loaded_textures_;
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(textureunit, sampler_id);

    stbi_image_free(data);

    loaded_textures_++;
    return textureunit;
}

void Renderer::DrawPhong(glm::mat4 model, Camera& cam, HitBox box, GLuint texture, GLuint vertex_array_id,
                         GLenum draw_mode, GLsizei el_count, GLenum type, void* first_index) {
    glUseProgram(phong_.GetId());

    glBindVertexArray(vertex_array_id);

    glUniformMatrix4fv(phong_.GetUniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(phong_.GetUniform("view"), 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
    glUniformMatrix4fv(phong_.GetUniform("projection"), 1, GL_FALSE, glm::value_ptr(perspective_));
    glUniform4fv(phong_.GetUniform("view_vec"), 1, glm::value_ptr(cam.GetViewVec()));
    glUniform4fv(phong_.GetUniform("bbox_min"), 1, glm::value_ptr(box.min_));
    glUniform4fv(phong_.GetUniform("bbox_max"), 1, glm::value_ptr(box.max_));
    glUniform1i(phong_.GetUniform("color_texture"), texture);

    glDrawElements(draw_mode, el_count, type, first_index);

    glBindVertexArray(0);
}
