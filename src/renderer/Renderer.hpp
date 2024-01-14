#pragma once

#include "Shader.hpp"
#include "renderer/GPUProgram.hpp"

class Renderer {
   public:
    Renderer();

   private:
    GPUProgram phong_;
    GPUProgram gouraud_;

};
