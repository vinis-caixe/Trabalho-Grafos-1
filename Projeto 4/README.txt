Trabalho de Grafos 4
Departamento de Ciência da Computação - UnB
Pedro Vitor Valença Mizuno - 17/0043665
Vinícius Caixeta de Souza - 18/0132199

O programa possui os arquivos main.c, lista.c e lista.h e foi feito no Linux Ubuntu 20.04 e compilado no GCC versão 9.3.0.
Para sua correta execução, é necessário ter no mesmo diretório o arquivo: arestas.txt

Compilar:
gcc main.c lista.c -o main

Executar:
./main

Como no segundo trabalho, criamos nossa própria função para gerar os arquivos .dot .
Os códigos dot, de nomes grafoInicial.dot e grafoColorido.dot, são gerados após a execução da main.

Para gerar a imagem do grafo sem cores, utilize esse comando:
dot -Tpng grafoInicial.dot -o grafoInicial.png

Para gerar a imagem do grafo colorido, utilize esse comando:
dot -Tpng grafoColorido.dot -o grafoColorido.png

Com esses comandos, as imagens grafoInicial.png e grafoColorido.png são geradas.