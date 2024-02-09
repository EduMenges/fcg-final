# fcg-final
Trabalho final de Fundamentos de Computação Gráfica

## Contribuições de cada membro
### Álvaro
Produção dos modelos e texturas dos ingredientes, garrafas, mesas e OVNI; implementação da colisão esfera-esfera; implementação das animações; implementação das transformações controladas por usuário (pegar e carregar ingrediente, adicionar ingrediente a hambúrguer, resetar hambúrguer).
### Eduardo
Estruturação do código; implementação dos modelos de iluminação; implementação das câmeras; implementação do sistema de curvas de Bézier; implementação das colisões cubo-cubo e raio-esfera; implementação do carregamento de modelos e texturas.

## Uso de assistentes IA
Foram feitas eventuais consultas ao ChatGPT e ao GitHub Copilot para auxílio na resolução de erros de compilação e verificação de dúvidas sintáticas. Nenhuma das ferramentas foi responsável por elaborar nenhuma parte dos algoritmos ou funções utilizadas no programa final, apenas por auxiliar na sua construção correta em C++. O Copilot foi, na maior parte, muito pouco útil. Ele frequentemente não mudou nada no código, ou propôs soluções que causaram ainda mais problemas. O ChatGPT, de maneira geral, foi muito mais útil, identificando erros ou más práticas no uso de C++ e de OpenGL, e sugerindo alguns recursos a utilizar.

## Processo de desenvolvimento
O programa foi desenvolvido em C++, com orientação a objetos. Houve um foco em contextualizar todos os requisitos técnicos do trabalho no universo do jogo. Foram produzidos modelos 3D e texturas especificamente para esta aplicação. Foram usadas malhas poligonais com mapeamento de textura para compor o cenário (paredes, chão, teto, mesas, geladeira, fogão) e os objetos interagíveis (ingredientes, hambúrguer, OVNI).
O jogo é primariamente controlado com câmera livre, havendo a possibilidade de usar câmera look-at para ver a receita a ser seguida. Objetos que aparecem múltiplas vezes (mesas e ingredientes) são instanciados usando diferentes matrizes de modelo, carregando seu modelo 3D uma vez apenas. As mesas e o chão usam iluminação difusa, enquanto os demais objetos usam iluminação de Blinn-Phong. A maioria dos objetos usa o modelo de interpolação de Phong, com a exceção das manchas de ketchup e mostarda, que usam o modelo de Gouraud.
O jogador pode provocar mudanças geométricas nos ingredientes, pegando-os e carregando-os consigo. Além disso, ao olhar para um modelo, este girará em seu lugar. Quando o jogador concluir o hambúrguer de acordo com a receita especificada, acontece uma "cutscene" na qual o hambúrguer é abduzido por um OVNI. Esta animação é baseada no tempo e utiliza uma curva de Bezier cúbica.
São usados três tipos de teste de intersecção: teste cubo-cubo, para testar a colisão do jogador com o ambiente; teste raio-esfera, para verificar que o jogador está clicando no ingrediente/hambúrguer; e teste esfera-esfera, para detectar o momento em que o OVNI deve parar sobre o hambúrguer.

## Instruções de uso
- Teclas WASD: movimentação do jogador
- Cursor do mouse: movimentação da câmera
- Tecla L: alterna entre câmera livre e look-at
- Botão esquerdo do mouse ou tecla E: pega ingrediente/adiciona ingrediente ao hambúrguer
- Botão direito do mouse ou tecla Q: devolve ingrediente sendo segurado
- Tecla Enter: verifica se o hambúrguer está certo de acordo com a receita
O objetivo do jogo consiste em montar o hambúrguer mostrado na tela de receita (aleatorizada toda vez que é rodado o jogo). Se a receita estiver incorreta, apertar a tecla Enter removerá todos os ingredientes adicionados, para que o jogador possa tentar novamente.

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
