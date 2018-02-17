#ifndef GRAFO__H
#define GRAFO__H
#include "Lista.h"
#include "Hash.h"

typedef void* Grafo;
typedef void* Vertice;
typedef void* Aresta;

/*ESTE EH O GRAFO TAD. POR DEFINICAO, GRAFOS SAO UTILIZADOS PARA GERENCIAR E TRATAR
DADOS QUE POSSUEM ALGUM TIPO DE RELACAO, ATRAVES DE VERTICES (OBJETO) E ARESTAS
(RELACAO ENTRE OS OBJETOS).
ESTE TAD PRODUZ GRAFOS DIRECIONADOS E PONDERADODS.
COMO O GRAFO EH GERENCIADO POR LISTAS, EH RECOMENDADO QUE ESTE TAD SEJA UTILIZADO
EM CASOS EM QUE O NUMERO DE ARESTAS NAO SEJA MUITO GRANDE, OU SEJA, O GRAU MAXIMO
DE CADA VERTICE SEJA UM VALOR BAIXO.*/

Grafo grafo_create(int size);
/*Cria um grafo e retorna-o*/

Vertice grafo_create_vertice(char *id, double x, double y);
/*Cria um vertice de nome ID, de coordenadas x e y no plano cartesiano*/

Aresta grafo_create_aresta(char *nome, char *ldir, char *lesq, double cmp, double vm);
/*Cria uma aresta identificada pelo nome, ldir e lesq sao os nomes das quadras a direita e esquerda
do ponto atual, cmp eh o comprimento e vm a velocidade media.*/

void grafo_insere_vertice(Grafo gra, Vertice v);
/*Insere um vertice na grafo Gra.
O vertice possui referencias x e y as suas posicoes no plano cartesiano invertido (SVG)*/

void grafo_insere_aresta(Grafo gra, Aresta A, Vertice V1, Vertice V2);
/*Insere uma aresta no grafo Gra que liga dois vertices definidos
na criacao da aresta.*/

Vertice grafo_search_vertice_id(Grafo G, char *id);
/*Retorna o vertice de nome "Id". O Grafo G deve existir*/

Lista grafo_get_allvertices(Grafo G);
/*Retorna todos os vertices do grafo g em uma lista.*/

Lista grafo_get_allarestas(Grafo G);
/*Retorna todas as arestas do grafo G em uma lista*/

Aresta grafo_get_aresta_ligacao(Grafo G, Vertice V1, Vertice V2);
/*Retorna a aresta que liga o vertice V1 ao V2, caso nao haja ligacao entre eles, retorna NULL.*/

void grafo_remove_aresta_ligacao(Grafo G, Vertice V1, Vertice V2);
/*Caso haja uma aresta que liga V1 a V2, remove.*/

int grafo_cond_adjacent(Grafo G, Vertice V1, Vertice V2);
/*Verifica se os vertices V1 e V2 sao adjacentes, ou seja, possuem uma aresta de ligacao.
Retorna 1 caso verdadeiro.
Retorna 0 caso falso.
*/

Lista grafo_get_vertices_adjacentes(Grafo G, Vertice V);
/*Retorna uma lista com todos vertices adjacentes ao vertice V, ou seja
todos o vertices que possuem ao menos uma ligacao com V.
Funcao ainda nao implementada.
*/

/*Getters*/
int grafo_get_grafo_size(Grafo G);
/*Retorna o tamanho do grafo G*/
char *grafo_get_vertice_id(Vertice V);
/*Retorna o Id do vertice V*/
int grafo_get_vertice_grau(Vertice V);
/*Retorna o grau (numero de arestas) do Vertice V*/
double grafo_get_vertice_x(Vertice V);
/*Retorna a posicao X do Vertice V*/
double grafo_get_vertice_y(Vertice V);
/*Retorna a posicao Y do Vertice V*/
double grafo_get_vertice_dist(Vertice V);
/*Retorna a distancia do Vertice V*/
Lista grafo_get_vertice_arestas(Vertice V);
/*Retorna uma Lista com todas as arestas do Vertice V*/
Vertice grafo_get_vertice_prev(Vertice V);
/*Retorna o prev do vertice V*/
char *grafo_get_aresta_nome(Aresta A);
/*Retorna o identificador nome da aresta A*/
char *grafo_get_aresta_ldir(Aresta A);
/*Retorna o nome da quadra a direita da aresta A*/
char *grafo_get_aresta_lesq(Aresta A);
/*Retorna o nome da quadra a esquerda da aresta A*/
double grafo_get_aresta_cmp(Aresta A);
/*Retorna o comprimento da Aresta A*/
double grafo_get_aresta_vm(Aresta A);
/*Retorna a velocidade media da Aresta A*/
Vertice grafo_get_aresta_ponta(Aresta A);
/*Retorna o vertice para onde a Aresta A aponta*/

/*FUNCOES TESTE*/
char *grafo_vertice_get_id(Vertice v);

double grafo_vertice_get_x(Vertice v);

void grafo_imprime_arestas_do_vertice(Vertice v);
#endif
