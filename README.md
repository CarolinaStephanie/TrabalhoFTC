# Trabalho Prático

Trabalho prático de Fundamentos Teóricos da Computação do Programa de Pós-graduação em Informática
Professor: Zenilton Kleber Gonçalves do Patrocínio Júnior
Alunas: Andressa Castro e Carolina Stephanie

## Getting Started

A implementação recebe um arquivo de entrada (input.txt) com várias sentenças e solicita digitar o nome de um arquivo que está na pasta expressões, contendo a descrição de uma ER qualquer (exp.jff, exp1.jff etc..). Em seguida, gera como saída outro arquivo contendo a descrição do AFD equivalente (AFD_GERADO.jff), além disso, é simulado o AFD para cada senteça do arquivo de entrada e na tela mostra se as sentenças pertencem ou não à linguagem da ER. Para simular uma sentença vazia o símbolo "-" é utilizado.

### Prerequisites

Compilador GCC

### Installing

Compilar o arquivo main.cpp

```
clang main.cpp -o main
```

```
gcc main.cpp -o main
```

E executar

```
./main
```
