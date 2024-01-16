#include "Renderer.hpp"
#include "stb/stb_image.h"

Renderer::Renderer() : phong_(shader::Vertex("../../shader/phong_vertex.glsl"),
                              shader::Fragment("../../shader/phong_fragment.glsl")),
                       gouraud_(shader::Vertex("../../shader/gouraud_vertex.glsl"),
                                shader::Fragment("../../shader/gouraud_fragment.glsl")) {

}
