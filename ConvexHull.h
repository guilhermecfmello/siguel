#ifndef ConvexHull_H
#define ConvexHull_H

#include "Lista.h"
#include "Pilha.h"
#include "Ordenacao.h"

typedef double(*getX)(void *p);
/*A FUNCAO DEVE RECEBER UM ELEMENTO (QUADRA, HIDRANTE, TORRE, SEMAFORO)
E RETORNAR SUA POSICAO X NO PLANO.
*/
typedef double(*getY)(void *p);
/*A FUNCAO DEVE RECEBER UM ELEMENTO (QUADRA, HIDRANTE, TORRE, SEMAFORO)
E RETORNAR SUA POSICAO Y NO PLANO.
*/
typedef void* Vector;

vectorNode *listToVector(Lista l, getX gx, getY gy);
/*RECEBE UMA LISTA DE ELEMENTOS QUAISQUER E RETORNA UM VETOR
DO TIPO "VECTORNODE" DA ORDENACAO. A LISTA NAO É APAGADA.
*/

Pilha convexHull(Lista l, getX gx, getY gy);
/*Recebe uma lista de elementos, e duas funcoes. Essa FUNCOES
devem retornar a coordenada x e y dos elementos da lista.
Convexhull retorna uma pilha com todos os elementos da lista
ordenados com envoltórios convexos, de fora para dentro.*/

Pilha calculaConvexHull(vectorNode *vector, int size, Pilha ch, Pilha inside);
/*Recebe um vetor do tipo vectorNode (Ver no modulo Ordenacao),
o tamanho do vetor, e duas pilhas.
Na pilha ch, a funcao colocara os pontos que fazem parte do envoltorio convexo.
Na pilha inside, colocara o restante.
*/

double ccw(vectorNode *v1, vectorNode *v2, vectorNode *v3);
/*ccw retorna 3 pontos de um vetor.
Retorno:
ccw = -1, se os 3 pontos formam caminho de angulo anti-horario.
ccw = 1, se o 3 pontos formam caminho de angulo em sentido horario.
ccw = 0, se os 3 pontos forem colineares.
*/

#endif
