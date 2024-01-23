#include "matrices.hpp"

glm::mat4 MatrixPerspective(float field_of_view, float aspect, float n, float f) {
    float const t = std::fabs(n) * std::tan(field_of_view / 2.0F);
    float const b = -t;
    float const r = t * aspect;
    float const l = -r;

    glm::mat4 const P = Matrix(n, 0.0F, 0.0F, 0.0F,        //
                               0.0F, n, 0.0F, 0.0F,        //
                               0.0F, 0.0F, n + f, -f * n,  //
                               0.0F, 0.0F, 1.0F, 0.0F);

    // A matriz M é a mesma computada acima em Matrix_Orthographic().
    glm::mat4 const M = MatrixOrthographic(l, r, b, t, n, f);

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

glm::mat4 MatrixRotateX(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix(1.0F, 0.0F, 0.0F, 0.0F,  //
                  0.0F, c, -s, 0.0F,       //
                  0.0F, s, c, 0.0F,        //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

glm::mat4 MatrixRotateY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix(c, 0.0F, s, 0.0F,        //
                  0.0F, 1.0F, 0.0F, 0.0F,  //
                  -s, 0.0F, c, 0.0F,       //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

glm::mat4 MatrixRotateZ(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Matrix(c, -s, 0.0F, 0.0F,       //
                  s, c, 0.0F, 0.0F,        //
                  0.0F, 0.0F, 1.0F, 0.0F,  //
                  0.0F, 0.0F, 0.0F, 1.0F);
}

float Norm(glm::vec4 v) {
    float vx = v.x;
    float vy = v.y;
    float vz = v.z;

    return std::sqrt(vx * vx + vy * vy + vz * vz);
}

glm::mat4 MatrixRotate(float angle, glm::vec4 axis) {
    float c = std::cos(angle);
    float s = std::sin(angle);

    glm::vec4 v = axis / Norm(axis);

    auto [vx, vy, vz, vw] = v;

    return Matrix(vx * vx * (1.0F - c) + c, vx * vy * (1.0F - c) - vz * s, vx * vz * (1 - c) + vy * s, 0.0F,  //
                  vx * vy * (1.0F - c) + vz * s, vy * vy * (1.0F - c) + c, vy * vz * (1 - c) - vx * s, 0.0F,  //
                  vx * vz * (1 - c) - vy * s, vy * vz * (1 - c) + vx * s, vz * vz * (1.0F - c) + c, 0.0F,     //
                  0.0F, 0.0F, 0.0F, 1.0F);
}
