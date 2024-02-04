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

uniform vec3 bbox_min;
uniform vec3 bbox_Max;

uniform float time;

uniform int use_texture;
uniform sampler2D color_texture;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
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
    //    vec4 l = normalize(vec4(1.0, 1.0, 0.0, 0.0));

    vec4 l = v;

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2 * n * (dot(n, l));

    // Parâmetros que definem as propriedades espectrais da superfície

    // Refletância difusa
    vec3 Kd = texture(color_texture, tex_coord).rgb;

    // Refletância especular
    vec3 Ks = vec3(0.8, 0.8, 0.8);
    // Refletância ambiente
    vec3 Ka = Kd * 0.05;
    // Expoente especular para o modelo de iluminação de Phong
    float q = 32;

    // Espectro da fonte de iluminação
    vec3 I = vec3(1, 1, 1);
    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2);

    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term = Ks * I * pow(max(0, dot(r, v)), q);

    // Iluminação
    color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0, 1.0, 1.0) / 2.2);
}
