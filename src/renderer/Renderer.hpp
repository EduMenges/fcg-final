#pragma once

#include "Singleton.hpp"
#include "Shader.hpp"
#include "renderer/GPUProgram.hpp"

class Renderer : public Singleton<Renderer> {
public:
    static void Init();

    Renderer();
private:
    GPUProgram phong_;
    GPUProgram gouraud_;
};
