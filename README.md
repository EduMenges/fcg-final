# fcg-final
Trabalho final de Fundamentos de Computação Gráfica

## Compilação

A compilação depende da plataforma do host. Em ambas plataformas, o CMake deve se encarregar de baixar as bibliotecas
auxiliares (GLM, tinyobjloader, tl::expected, ...). Já o sistema de build (Ninja) deve ser instalado manualmente pelo
usuário.

Presumimos que o usuário tem acesso a um compiladora que suporta a padronização 20 do C++, ainda que parcialmente. Os
autores usaram o GCC, versão 11.4.0.

### Windows

Basta realizar os comandos

```powershell
cmake --preset windows
cmake --build --preset windows-debug
```

### Linux

Basta realizar os comandos

```bash
cmake --preset linux
cmake --build --preset linux-debug
```

Para compilar em modo `release`, basta trocar para `linux-release`.

## Requisitos

### Do Gastal

- [X] Malhas poligonais complexas
- [X] Transformações geométricas controladas pelo usuário
- [X] Câmera livre
- [ ] Câmera look-at
- [X] Instâncias de objetos
- [ ] Três tipos de testes de intersecção
  - [X] Cubo-cubo
  - [X] Raio-esfera
- [X] Modelos de Iluminação Difusa e Blinn-Phong
- [X] Modelo de Interpolação de Phong
- [X] Modelo de Interpolação de Goraud
- [X] Mapeamento de texturas em todos os objetos
- [X] Movimentação com curva Bézier cúbica
- [X] Animações baseadas no tempo

### Nossos

- [X] Avaliação do pedido
- [X] Lógica para pegar os objetos interagíveis
- [X] Skybox ou paredes
- [ ] Colisão gota de ketchup
- [ ] Funcionalidade de fritar hamburguer (e ovo?)
- [ ] UI simples (pedido, tempo, pontuação)
