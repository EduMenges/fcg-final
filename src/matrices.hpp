#pragma once

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "fmt/core.h"
#include <stdexcept>

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

constexpr glm::mat4 MatrixTranslate(glm::vec3 point) { return MatrixTranslate(point.x, point.y, point.z); }

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

constexpr glm::mat4 MatrixScale(glm::vec3 point) { return MatrixScale(point.x, point.y, point.z); }

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo X (primeiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ px, c*py-s*pz, s*py+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 MatrixRotateX(float angle);

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Y (segundo vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px+s*pz, py, -s*px+c*pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 MatrixRotateY(float angle);

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo Z (terceiro vetor da base do sistema de
// coordenadas). Seja p=[px,py,pz,pw] um ponto em coordenadas homogêneas.
// Então, a matriz R é definida pela seguinte igualdade:
//
//   R*p = [ c*px-s*py, s*px+c*py, pz, pw ];
//
// onde 'c' e 's' são o cosseno e o seno do ângulo de rotação, respectivamente.
glm::mat4 MatrixRotateZ(float angle);

// Função que calcula a norma Euclidiana de um vetor cujos coeficientes são
// definidos em uma base ortonormal qualquer.
float Norm(glm::vec4 v);

inline glm::vec4 Normalize(glm::vec4 v) { return (v / Norm(v)); }

// Matriz R de "rotação de um ponto" em relação à origem do sistema de
// coordenadas e em torno do eixo definido pelo vetor 'axis'. Esta matriz pode
// ser definida pela fórmula de Rodrigues. Lembre-se que o vetor que define o
// eixo de rotação deve ser normalizado!
glm::mat4 MatrixRotate(float angle, glm::vec4 axis);

// Produto vetorial entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
constexpr glm::vec4 CrossProduct(glm::vec4 u, glm::vec4 v) {
    auto [u1, u2, u3, _u4] = u;
    auto [v1, v2, v3, _v4] = v;

    return {
        u2 * v3 - u3 * v2,  //
        u3 * v1 - u1 * v3,  //
        u1 * v2 - u2 * v1,  //
        0.0F                //
    };
}

// Produto escalar entre dois vetores u e v definidos em um sistema de
// coordenadas ortonormal.
constexpr float DotProduct(glm::vec4 u, glm::vec4 v) {
    auto [u1, u2, u3, u4] = u;
    auto [v1, v2, v3, v4] = v;

    if (u4 != 0.0F || v4 != 0.0F) {
        throw std::runtime_error("Dot product não está definido para pontos");
    }

    return u1 * v1 + u2 * v2 + u3 * v3;
}

// Matriz de mudança de coordenadas para o sistema de coordenadas da Câmera.
glm::mat4 MatrixCameraView(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector);

// Matriz de projeção paralela ortográfica
constexpr glm::mat4 MatrixOrthographic(float l, float r, float b, float t, float n, float f) {
    return Matrix(2.0F / (r - l), 0.0F, 0.0F, -(r + l) / (r - l),  //
                  0.0F, 2.0F / (t - b), 0.0F, -(t + b) / (t - b),  //
                  0.0F, 0.0F, 2.0F / (f - n), -(f + n) / (f - n),  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

// Matriz de projeção perspectiva
glm::mat4 MatrixPerspective(float field_of_view, float aspect, float n, float f);
