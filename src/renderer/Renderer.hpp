#pragma once

#include "Shader.hpp"
#include "renderer/GPUProgram.hpp"

class Renderer {
public:
    static Renderer& Instance() {
        static Renderer instance;
        return instance;
    }

private:
    Renderer();

    GPUProgram phong_;
    GPUProgram gouraud_;
};
