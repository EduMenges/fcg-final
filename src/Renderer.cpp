#include "Renderer.hpp"
#include "fmt/core.h"
#include "stb/stb_image.h"

void Renderer::LoadTextureImage(const std::filesystem::path& filename) {
    fmt::println("{}: loading image \"{}\"", __func__, filename.string().c_str());

    // Primeiro fazemos a leitura da imagem do disco
    stbi_set_flip_vertically_on_load(1);
    int   width, height, channels; // NOLINT(*-isolate-declaration)
    auto* data = stbi_load(filename.string().c_str(), &width, &height, &channels, 3);

    if (data == nullptr) {
        auto error = std::make_error_code(static_cast<std::errc>(errno));
        throw std::filesystem::filesystem_error("Could not open image", error);
    }

    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint texture_unit = loaded_textures_;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(texture_unit, sampler_id);

    stbi_image_free(data);

    loaded_textures_ += 1;
}
