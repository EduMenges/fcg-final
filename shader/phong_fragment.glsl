#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 vertex_color;
in vec4 position_world;
in vec4 normal;
in vec2 tex_coord;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 view_vec;

uniform int use_texture;
uniform sampler2D color_texture;
uniform vec3 Kd_notexture;

// Refletância especular
uniform vec3 Ks;

// Refletância ambiente
uniform vec3 Ka;

// Expoente especular para o modelo de iluminação de bling-phong
// É o "shininess" do material
uniform float q;

// O valor de saída ("out") de um Fragment Shader, a cor final do fragmento.
out vec4 color;

void main()
{
    if (use_texture == 0) {
        discard;
    }

    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = v;

    // Parâmetros que definem as propriedades espectrais da superfície

    // Refletância difusa
    vec3 Kd;

    if (use_texture == 1) {
        Kd = texture(color_texture, tex_coord).rgb;
    } else {
        Kd = Kd_notexture;
    }

    // Espectro da fonte de iluminação
    vec3 I = vec3(0.5, 0.5, 0.5);

    // Espectro da luz ambiente
    vec3 Ia = vec3(0.0, 0.0, 0.0);

    // Halfway vector
    vec4 h = normalize(v + l);

    // Diffuse lighting
    vec3 lambert_diffuse_term = Kd * I * max(0.0, dot(n, l));

    // Specular lighting
    float specularFactor = pow(max(dot(h, n), 0.0), q);
    vec3 bling_phong_specular_term = Ks * I * specularFactor;

    vec3 ambient_term = Ka * Ia;
    vec3 result = lambert_diffuse_term + ambient_term + bling_phong_specular_term;

    // Iluminação
    color.rgb = clamp(result, 0.0, 1.0);

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0, 1.0, 1.0) / 2.2);
}
