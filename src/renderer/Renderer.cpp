#include "Renderer.hpp"
#include "fmt/core.h"
#include "stb/stb_image.h"

std::unique_ptr<Renderer> Renderer::instance_ = nullptr;

Renderer::Renderer(): phong_(shader::Vertex("../../shader/phong_vertex.glsl"), shader::Fragment("../../shader/phong_fragment.glsl")),
                       gouraud_(shader::Vertex("../../shader/gouraud_vertex.glsl"), shader::Fragment("../../shader/gouraud_fragment.glsl")){
    phong_.InsertLocation("model", "view", "projection", "view_vec", "bbox_min", "bbox_max", "color_texture", "time");
    gouraud_.InsertLocation("model", "view", "projection", "view_vec", "color_texture", "time");
}
