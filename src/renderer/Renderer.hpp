#pragma once

#include "Shader.hpp"
#include "renderer/GPUProgram.hpp"

class Renderer {
   public:
    Renderer(const Renderer& other) = delete;

    static const Renderer& Get() {
        if (instance_ == nullptr) {
            Init();
        }
        return *instance_;
    }

    static Renderer& GetMut() {
        if (instance_ == nullptr) {
            Init();
        }
        return *instance_;
    }

   private:
    static void Init() { instance_ = std::unique_ptr<Renderer>(new Renderer); }

#pragma clang diagnostic push
#pragma ide diagnostic   ignored "hicpp-use-equals-delete"
    Renderer();
#pragma clang diagnostic pop

    static std::unique_ptr<Renderer> instance_;

    GPUProgram phong_;
    GPUProgram gouraud_;
};
