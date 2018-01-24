#ifndef GRAFO__H
#define GRAFO__H

#include "Lista.h"

typedef void* Grafo;

Grafo grafo_create(int n);
/*Cria um grafo contendo n vertices e zero arestas*/

void grafo_insere_aresta(Grafo gra, int v1, int v2);
/*v1 e v2 devem pertencer ao conjunto de vertices;
Insere no grafo uma aresta nos vertices v1 e v2;
*/

void grafo_define_info(Grafo gra, int v1, int v2, void *info);
/*v1 e v1 devem pertencer ao grafo.
Adiciona o conteudo info a aresta v1,v2 do grafo.
*/

void* grafo_getInfo(Grafo gra, int v1, int v2);
/*v1 e v2 devem pertencer ao grafo.
Retorna o conteudo pertencente a aresta v1,v2 do grafo.
*/

void grafo_remove_aresta(Grafo gra, int v1, int v2);
/*v1 e v2 devem pertencer ao grafo.
Remove a aresta correspondente aos vertices v1 e v2 do grafo.
*/

int grafo_adjacente(Grafo gra, int v1, int v2);
/*v1 e v2 devem pertencer ao grafo.
retorna 1 se v1 e v2 forem vizinhos.
retorna 0 caso contrario.
*/

Lista grafo_adjacentes(Grafo gra, int v);
/*v deve pertencer ao grafo
Retorna uma lista contento todos os vertices adjacentes ao vertice v;
*/



#endif
