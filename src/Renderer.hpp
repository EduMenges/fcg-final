#pragma once

#include "Shader.hpp"
#include "GPUProgram.hpp"

class Renderer {
   public:
    Renderer()
        : program_(VertexShader("../../src/shader_vertex.glsl"), FragmentShader("../../src/shader_fragment.glsl")) {}

    void LoadTextureImage(const std::filesystem::path& filename);

   private:
    GPUProgram program_;
    GLuint loaded_textures_ = 0;

};
