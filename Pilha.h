#ifndef PILHA__H
#define PILHA__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*UMA PILHA AGRUPA QUALQUER TIPO DE DADO, NA FORMA EM QUE O PRIMEIRO
ITEM INCLUSO É O ULTIMO ITEM A SER RETIRADO. PODEMOS UTILIZAR FUNCOES QUE
PEGAM SEU TAMANHO E QUE PEGAM O ELEMENTO DO TOPO DA PILHA, UMA PILHA SEM ELEMENTOS
TEM TAMANO = 0*/

typedef void *PosicP;
typedef void *Pilha;

Pilha createPilha();
/*Cria uma pilha vazia
*/
PosicP topPilha(Pilha pil);

PosicP nextTopPilha(Pilha pil);

void push(Pilha pil, PosicP elemento);
/*Adiciona um elemento no topo da pilha
*/

PosicP pop(Pilha pil);
/*Retorna o elemento do topo da pilha
Retira o elemento retornado da pilha;
*/

int getSizePilha(Pilha pil);
/*Retorna o tamanho da pilha, ou seja,
o numero de elementos que ela possui.
*/
#endif
