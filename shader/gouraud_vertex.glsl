#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
layout (location = 3) in vec4 color_coefficients;

out vec4 vertexColor;
out vec4 positionWorld;
out vec4 normal;
out vec2 tex_coord;

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

uniform float dissolve;

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    vertexColor = color_coefficients;

    positionWorld = model * model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    tex_coord = texture_coefficients;

    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = positionWorld;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = v;

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2 * n * (dot(n, l));

    // Parâmetros que definem as propriedades espectrais da superfície
    // Refletância difusa
    vec3 Kd;

    if (use_texture == 1) {
        Kd = texture(color_texture, tex_coord).rgb;
    } else {
        Kd = Kd_notexture;
    }

    // Espectro da fonte de iluminação
    vec3 I = vec3(1.0, 1.0, 1.0);
    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2);

    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
    vec3 ambient_term = Ka * Ia;
    vec3 phong_specular_term = Ks * I * pow(max(0, dot(r, v)), q);

    // Illumination
    vec3 result = lambert_diffuse_term + ambient_term + phong_specular_term;
    vertexColor.rgb = clamp(result, 0.0, 1.0);

    // Cor final com correção gamma, considerando monitor sRGB.
    vertexColor.rgb = pow(vertexColor.rgb, vec3(1.0, 1.0, 1.0) / 2.2);
    vertexColor.a = dissolve;
}

