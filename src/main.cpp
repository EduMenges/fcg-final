#include <iostream>
#include "matrices.hpp"

int main() {
    auto identity = MatrixIdentity();
    auto teste = identity * MatrixRotateX(0.5);

    std::cout << "Hello World!\n";
}
