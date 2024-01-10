#pragma once

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "fmt/core.h"

// Esta função Matrix() auxilia na criação de matrizes usando a biblioteca GLM.
// Note que em OpenGL (e GLM) as matrizes são definidas como "column-major",
// onde os elementos da matriz são armazenadas percorrendo as COLUNAS da mesma.
// Por exemplo, seja
//
//       [a b c]
//   M = [d e f]
//       [g h i]
//
// uma matriz 3x3. Em memória, na representação "column-major" de OpenGL, essa
// matriz é representada pelo seguinte array:
//
//   M[] = {  a,d,g,    b,e,h,    c,f,i  };
//              ^         ^         ^
//              |         |         |
//           coluna 1  coluna 2  coluna 3
//
// Para conseguirmos definir matrizes através de suas LINHAS, a função Matrix()
// computa a transposta usando os elementos passados por parâmetros.
constexpr glm::mat4 Matrix(float m00, float m01, float m02, float m03,  // LINHA 1
                           float m10, float m11, float m12, float m13,  // LINHA 2
                           float m20, float m21, float m22, float m23,  // LINHA 3
                           float m30, float m31, float m32, float m33   // LINHA 4
) {
    return {
        m00, m10, m20, m30,  // COLUNA 1
        m01, m11, m21, m31,  // COLUNA 2
        m02, m12, m22, m32,  // COLUNA 3
        m03, m13, m23, m33   // COLUNA 4
    };
}

/// Matriz identidade.
constexpr glm::mat4 MatrixIdentity() {
    return Matrix(1.0F, 0.0F, 0.0F, 0.0F,  // LINHA 1
                  0.0F, 1.0F, 0.0F, 0.0F,  // LINHA 2
                  0.0F, 0.0F, 1.0F, 0.0F,  // LINHA 3
                  0.0F, 0.0F, 0.0F, 1.0F   // LINHA 4
    );
}

// Matriz de translação T. Seja p=[px,py,pz,pw] um ponto e t=[tx,ty,tz,0] um
// vetor em coordenadas homogêneas, definidos em um sistema de coordenadas
// Cartesiano. Então, a matriz T é definida pela seguinte igualdade:
//
//     T*p = p+t.
//
constexpr glm::mat4 MatrixTranslate(float tx, float ty, float tz) {
    return Matrix(1.0F, 0.0F, 0.0F, tx,  //
                  0.0F, 1.0F, 0.0F, ty,  //
                  0.0F, 0.0F, 1.0F, tz,  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz S de "escalamento de um ponto" em relação à origem do sistema de
// coordenadas. Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz S é definida pela seguinte igualdade:
//
//     S*p = [sx*px, sy*py, sz*pz, pw].
//
constexpr glm::mat4 MatrixScale(float sx, float sy, float sz) {
    return Matrix(sx, 0.0F, 0.0F, 0.0F,  //
                  0.0F, sy, 0.0F, 0.0F,  //
                  0.0F, 0.0F, sz, 0.0F,  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo X (primeiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ px, c*py-s*pz, s*py+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
constexpr glm::mat4 MatrixRotateX(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    return Matrix(1.0F, 0.0F, 0.0F, 0.0F,  //
                  0.0F, c, -s, 0.0F,       //
                  0.0F, s, c, 0.0F,        //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Y (segundo vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px+s*pz, py, -s*px+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
constexpr glm::mat4 MatrixRotateY(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    return Matrix(c, 0.0F, s, 0.0F,        //
                  0.0F, 1.0F, 0.0F, 0.0F,  //
                  -s, 0.0F, c, 0.0F,       //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Z (terceiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px-s*py, s*px+c*py, pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
constexpr glm::mat4 MatrixRotateZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    return Matrix(c, -s, 0.0F, 0.0F,       //
                  s, c, 0.0F, 0.0F,        //
                  0.0F, 0.0F, 1.0F, 0.0F,  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Função que calcula a norma Euclidiana de um vetor cujos coeficientes são
// definidos em uma base ortonormal qualquer.
constexpr float Norm(glm::vec4 v) {
    float vx = v.x;
    float vy = v.y;
    float vz = v.z;

    return sqrt(vx * vx + vy * vy + vz * vz);
}

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo definido pelo vetor 'axis'. Esta matriz pode
// ser definida pela fórmula de Rodrigues. Lembre-se que o vetor que define o
// eixo de rotação deve ser normalizado!
constexpr glm::mat4 MatrixRotate(float angle, glm::vec4 axis) {
    float c = cos(angle);
    float s = sin(angle);

    glm::vec4 v = axis / Norm(axis);

    float vx = v.x;
    float vy = v.y;
    float vz = v.z;

    return Matrix(vx * vx * (1.0F - c) + c, vx * vy * (1.0F - c) - vz * s, vx * vz * (1 - c) + vy * s, 0.0F,  //
                  vx * vy * (1.0F - c) + vz * s, vy * vy * (1.0F - c) + c, vy * vz * (1 - c) - vx * s, 0.0F,  //
                  vx * vz * (1 - c) - vy * s, vy * vz * (1 - c) + vx * s, vz * vz * (1.0F - c) + c, 0.0F,     //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Produto vetorial entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
constexpr glm::vec4 CrossProduct(glm::vec4 u, glm::vec4 v) {
    float u1 = u.x;
    float u2 = u.y;
    float u3 = u.z;
    float v1 = v.x;
    float v2 = v.y;
    float v3 = v.z;

    return glm::vec4(u2 * v3 - u3 * v2,  // Primeiro coeficiente
                     u3 * v1 - u1 * v3,  // Segundo coeficiente
                     u1 * v2 - u2 * v1,  // Terceiro coeficiente
                     0.0F                // w = 0 para vetores.
    );
}

// Produto escalar entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
constexpr float DotProduct(glm::vec4 u, glm::vec4 v) {
    float u1 = u.x;
    float u2 = u.y;
    float u3 = u.z;
    float u4 = u.w;
    float v1 = v.x;
    float v2 = v.y;
    float v3 = v.z;
    float v4 = v.w;

    if (u4 != 0.0F || v4 != 0.0F) {
        fmt::println(stderr, "Dot product não está definido para pontos.");
        std::terminate();
    }

    return u1 * v1 + u2 * v2 + u3 * v3;
}

// Matriz de mudança de coordenadas para o sistema de coordenadas da Câmera.
constexpr glm::mat4 MatrixCameraView(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector) {
    glm::vec4 w = -view_vector;
    glm::vec4 u = CrossProduct(up_vector, w);

    // Normalizamos os vetores u e w
    w = w / Norm(w);
    u = u / Norm(u);

    glm::vec4 v = CrossProduct(w, u);

    glm::vec4 origin_o = glm::vec4(0.0F, 0.0F, 0.0F, 1.0F);

    float ux = u.x;
    float uy = u.y;
    float uz = u.z;
    float vx = v.x;
    float vy = v.y;
    float vz = v.z;
    float wx = w.x;
    float wy = w.y;
    float wz = w.z;

    return Matrix(ux, uy, uz, -DotProduct(u, position_c - origin_o),  //
                  vx, vy, vz, -DotProduct(v, position_c - origin_o),  //
                  wx, wy, wz, -DotProduct(w, position_c - origin_o),  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz de projeção paralela ortográfica
constexpr glm::mat4 Matrix_Orthographic(float l, float r, float b, float t, float n, float f) {
    return Matrix(2.0F / (r - l), 0.0F, 0.0F, -(r + l) / (r - l),  //
                  0.0F, 2.0F / (t - b), 0.0F, -(t + b) / (t - b),  //
                  0.0F, 0.0F, 2.0F / (f - n), -(f + n) / (f - n),  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz de projeção perspectiva
inline glm::mat4 MatrixPerspective(float field_of_view, float aspect, float n, float f) {
    float t = fabs(n) * tanf(field_of_view / 2.0F);
    float b = -t;
    float r = t * aspect;
    float l = -r;

    glm::mat4 P = Matrix(n, 0.0F, 0.0F, 0.0F, 0.0F, n, 0.0F, 0.0F, 0.0F, 0.0F, n + f, -f * n, 0.0F, 0.0F, 1.0F, 0.0F);

    // A matriz M é a mesma computada acima em Matrix_Orthographic().
    glm::mat4 M = Matrix_Orthographic(l, r, b, t, n, f);

    // Note que as matrizes M*P e -M*P fazem exatamente a mesma projeção
    // perspectiva, já que o sinal de negativo não irá afetar o resultado
    // devido à divisão por w. Por exemplo, seja q = [qx,qy,qz,1] um ponto:
    //
    //      M*P*q = [ qx', qy', qz', w ]
    //   =(div w)=> [ qx'/w, qy'/w, qz'/w, 1 ]   Eq. (*)
    //
    // agora com o sinal de negativo:
    //
    //     -M*P*q = [ -qx', -qy', -qz', -w ]
    //   =(div w)=> [ -qx'/-w, -qy'/-w, -qz'/-w, -w/-w ]
    //            = [ qx'/w, qy'/w, qz'/w, 1 ]   Eq. (**)
    //
    // Note que o ponto final, após divisão por w, é igual: Eq. (*) == Eq. (**).
    //
    // Então, por que utilizamos -M*P ao invés de M*P? Pois a especificação de
    // OpenGL define que os pontos fora do cubo unitário NDC deverão ser
    // descartados já que não irão aparecer na tela. O teste que define se um ponto
    // q está dentro do cubo unitário NDC pode ser expresso como:
    //
    //      -1 <= qx'/w <= 1   &&  -1 <= qy'/w <= 1   &&  -1 <= qz'/w <= 1
    //
    // ou, de maneira equivalente SE w > 0, a placa de vídeo faz o seguinte teste
    // ANTES da divisão por w:
    //
    //      -w <= qx' <= w   &&  -w <= qy' <= w   &&  -w <= qz' <= w
    //
    // Note que o teste acima economiza uma divisão por w caso o ponto seja
    // descartado (quando esteja fora de NDC), entretanto, este último teste só
    // é equivalente ao primeiro teste SE E SOMENTE SE w > 0 (isto é, se w for
    // positivo). Como este último teste é o que a placa de vídeo (GPU) irá fazer,
    // precisamos utilizar a matriz -M*P para projeção perspectiva, de forma que
    // w seja positivo.
    //
    return -M * P;
}

// Função que imprime uma matriz M no terminal
void PrintMatrix(glm::mat4 M) {
    printf("\n");
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ]\n", M[0][0], M[1][0], M[2][0], M[3][0]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ]\n", M[0][1], M[1][1], M[2][1], M[3][1]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ]\n", M[0][2], M[1][2], M[2][2], M[3][2]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ]\n", M[0][3], M[1][3], M[2][3], M[3][3]);
}

// Função que imprime um vetor v no terminal
void PrintVector(glm::vec4 v) {
    printf("\n");
    printf("[ %+0.2F ]\n", v[0]);
    printf("[ %+0.2F ]\n", v[1]);
    printf("[ %+0.2F ]\n", v[2]);
    printf("[ %+0.2F ]\n", v[3]);
}

// Função que imprime o produto de uma matriz por um vetor no terminal
void PrintMatrixVectorProduct(glm::mat4 M, glm::vec4 v) {
    auto r = M * v;
    printf("\n");
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]\n", M[0][0], M[1][0], M[2][0], M[3][0], v[0],
           r[0]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ] = [ %+0.2F ]\n", M[0][1], M[1][1], M[2][1], M[3][1], v[1],
           r[1]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]\n", M[0][2], M[1][2], M[2][2], M[3][2], v[2],
           r[2]);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]\n", M[0][3], M[1][3], M[2][3], M[3][3], v[3],
           r[3]);
}

// Função que imprime o produto de uma matriz por um vetor, junto com divisão
// por w, no terminal.
void PrintMatrixVectorProductDivW(glm::mat4 M, glm::vec4 v) {
    auto r = M * v;
    auto w = r[3];
    printf("\n");
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]            [ %+0.2F ]\n", M[0][0], M[1][0],
           M[2][0], M[3][0], v[0], r[0], r[0] / w);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ] = [ %+0.2F ] =(div w)=> [ %+0.2F ]\n", M[0][1], M[1][1],
           M[2][1], M[3][1], v[1], r[1], r[1] / w);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]            [ %+0.2F ]\n", M[0][2], M[1][2],
           M[2][2], M[3][2], v[2], r[2], r[2] / w);
    printf("[ %+0.2F  %+0.2F  %+0.2F  %+0.2F ][ %+0.2F ]   [ %+0.2F ]            [ %+0.2F ]\n", M[0][3], M[1][3],
           M[2][3], M[3][3], v[3], r[3], r[3] / w);
}
