#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Grafo.h"

#define INFINITO 1.7*pow(10,307)

typedef struct _grafo{
  Hash vertices;
  int size;
}grafo;

typedef struct _vertice{
  char *id;
  int grau;
  double x;
  double y;
  double dist;
  Lista arestas;
  struct _vertice *prev;
}vertice;

typedef struct _aresta{
  char *nome;
  char *ldir;
  char *lesq;
  double cmp;
  double vm;
  double tempo;
  Vertice ponta;
}aresta;

Grafo grafo_create(int size){
  grafo *g;
  g = malloc(sizeof(grafo));
  if(g!=NULL){
    g->size = size;
    g->vertices = createHash(size);
  }
  return g;
}

Vertice grafo_create_vertice(char *id, double x, double y){
  vertice *v;
  v = malloc(sizeof(vertice));
  if(v!=NULL){
    v->grau = 0;
    v->x = x;
    v->y = y;
    v->dist = -1;
    v->prev = NULL;
    v->arestas = createList();
    v->id = malloc(sizeof(char)*(strlen(id)+1));
    strcpy(v->id,id);
  }
  return v;
}

Aresta grafo_create_aresta(char *nome, char *ldir, char *lesq, double cmp, double vm){
  aresta *a;

  a = malloc(sizeof(aresta));
  if(a!=NULL){
    a->cmp = cmp;
    a->vm = vm;
    a->nome = malloc(sizeof(char)*(strlen(nome)+1));
    a->ldir = malloc(sizeof(char)*(strlen(ldir)+1));
    a->lesq = malloc(sizeof(char)*(strlen(lesq)+1));
    strcpy(a->nome, nome);
    strcpy(a->ldir, ldir);
    strcpy(a->lesq, lesq);
    if(vm!=0)
      a->tempo = cmp/vm;
    else
      a->tempo = 0;
  }
  return a;
}

void grafo_insere_vertice(Grafo gra, Vertice V){
  grafo *g;
  vertice *v;

  g = (grafo*) gra;
  v = (vertice*) V;
  hash_insert(g->vertices,v,v->id);
}

Vertice grafo_search_vertice_id(Grafo G, char *id){
  grafo *g;
  Vertice v;

  g = (grafo*) G;
  v = hash_search(g->vertices, id);
  return v;
}

Lista grafo_get_allvertices(Grafo G){
  int i;
  grafo *g;
  Lista list, newList;
  Posic aux, reg, item;

  g = (grafo*) G;
  newList = createList();
  for(i=0;i<g->size;i++){
    list = hash_get_position(g->vertices,i);
    aux = getFirst(list);
    while(aux!=NULL){
      reg = get(list,aux);
      item = hash_get_reg(reg);
      insert(newList,item);
      aux = getNext(list,aux);
    }
  }
  return newList;
}

int grafo_cond_adjacent(Grafo G, Vertice V1, Vertice V2){
  vertice *v;
  aresta *a;
  Lista list;
  Posic aux;

  v = (vertice*) V1;
  list = v->arestas;
  aux = getFirst(list);
  while(aux!=NULL){
    a = (aresta*) get(list,aux);
    if(a->ponta==V2)
      return 1;
    aux = getNext(list,aux);
  }
  return 0;
}

void grafo_insere_aresta(Grafo gra, Aresta A, Vertice V1, Vertice V2){
  aresta *a;
  vertice *v;

  a = (aresta*) A;
  v = (vertice*) V1;
  a->ponta = V2;
  insert(v->arestas,a);
}

Aresta grafo_get_aresta_ligacao(Grafo G, Vertice V1, Vertice V2){
  vertice *v;
  aresta *a;
  Lista list;
  Posic aux;

  v = (vertice*) V1;
  list = v->arestas;
  aux = getFirst(list);
  while(aux!=NULL){
    a = (aresta*) get(list,aux);
    if(a->ponta==V2)
      return a;
    aux = getNext(list,aux);
  }
  return NULL;
}

void grafo_remove_aresta_ligacao(Grafo G, Vertice V1, Vertice V2){
  vertice *v;
  aresta *a, *item;
  Lista list;
  Posic aux;

  v = (vertice*) V1;
  list = v->arestas;
  aux = getFirst(list);
  while(aux!=NULL){
    item = (aresta*) get(list,aux);
    if(item->ponta == V2){
      remover(list,aux);
      break;
    }
    aux = getNext(list,aux);
  }
}

Lista grafo_get_allarestas(Grafo G){
  int i, size;
  grafo *g;
  vertice *v;
  RegH r;
  Hash h;
  Lista list, vertices, arestas;
  Posic aux, aux2, auxL, a;

  list = createList();
  g = (grafo*) G;
  for(i=0;i<g->size;i++){
    vertices = hash_get_position(g->vertices,i);
    aux = getFirst(vertices);
    while(aux!=NULL){
      auxL = get(vertices,aux);
      v = (vertice*) hash_get_reg(auxL);

      arestas = v->arestas;
      aux2 = getFirst(arestas);
      while(aux2!=NULL){
        a = get(arestas,aux2);
        /*printf("\n###TESTE: %s", a->nome);*/
        insert(list,a);
        aux2 = getNext(arestas,aux2);
      }
      aux = getNext(vertices,aux);
    }
  }
  return list;
}

Lista grafo_get_vertices_adjacentes(Grafo G, Vertice V){
  vertice *v;
  aresta *a;
  grafo *g;
  Lista newList;
  Posic aux;

  v = (vertice*) V;
  g = (grafo*) G;
  newList = createList();
  aux = getFirst(v->arestas);
  while(aux!=NULL){
    a = (aresta*) get(v->arestas, aux);
    insert(newList, a->ponta);
    aux = getNext(v->arestas, aux);
  }
  return newList;
}

Pilha grafo_melhor_caminho(Grafo G, Vertice V1, Vertice V2, char tipo){
  int i;
  vertice *v, *aux;
  Pilha final;
  Lista vertices;
  Posic node;

  vertices = grafo_get_allvertices(G);

  grafo_inicializa_dijkstra(vertices,V1);

  while(length(vertices)>0){
    node = grafo_calcula_aresta_menor_peso(vertices);
    v = get(vertices,node);
    remover(vertices, node);

    if(v==V2)
      break;
    grafo_relaxamento_arestas(G,v,tipo);
  }
  final = createPilha();
  while(v!=NULL){
    push(final,v);
    v = v->prev;
  }
  return final;
}

void grafo_inicializa_dijkstra(Lista vertices, Vertice v1){
  vertice *v;
  Posic aux;

  aux = getFirst(vertices);
  while(aux!=NULL){
    v = get(vertices, aux);
    v->dist = INFINITO;
    v->prev = NULL;
    aux = getNext(vertices,aux);
  }
  v = (vertice*) v1;
  v->dist = 0;
}

void grafo_relaxamento_arestas(Grafo G, Vertice V, char tipo){
  double alt;
  vertice *vzero, *v;
  aresta *a;
  grafo *g;
  Lista vizinhos;
  Posic aux;

  vzero = (vertice*) V;
  g = (grafo*) G;
  vizinhos = grafo_get_vertices_adjacentes(G, V);
  aux = getFirst(vizinhos);
  while(aux!=NULL){
    v = (vertice*) get(vizinhos,aux);
    alt = vzero->dist;
    a = (aresta*) grafo_get_aresta_ligacao(G,vzero,v);

    if(tipo=='D'){
      alt += a->cmp;
    }
    else if(tipo=='T'){
      alt += a->tempo;
    }
    if(alt<v->dist){
      v->dist = alt;
      v->prev = vzero;
    }
    aux = getNext(vizinhos,aux);
  }

}

Posic grafo_calcula_aresta_menor_peso(Lista vertices){
  double min;
  vertice *v;
  Posic aux, auxMin;

  min = INFINITO;
  aux = getFirst(vertices);
  auxMin = aux;
  while(aux!=NULL){
    v = (vertice*) get(vertices,aux);
    if(v->dist<min){
      min = v->dist;
      auxMin = aux;
    }
    aux = getNext(vertices,aux);
  }

  return auxMin;
}


/*Getters*/

int grafo_get_grafo_size(Grafo G){
  grafo *g;
  g = (grafo*) G;
  return g->size;
}

char *grafo_get_vertice_id(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->id;
}

int grafo_get_vertice_grau(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->grau;
}

double grafo_get_vertice_x(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->x;
}

double grafo_get_vertice_y(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->y;
}

double grafo_get_vertice_dist(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->dist;
}

Lista grafo_get_vertice_arestas(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->arestas;
}

Vertice grafo_get_vertice_prev(Vertice V){
  vertice *v;

  v = (vertice*) V;
  return v->prev;
}

char *grafo_get_aresta_nome(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->nome;
}

char *grafo_get_aresta_ldir(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->ldir;
}

char *grafo_get_aresta_lesq(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->lesq;
}

double grafo_get_aresta_cmp(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->cmp;
}

double grafo_get_aresta_vm(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->vm;
}

Vertice grafo_get_aresta_ponta(Aresta A){
  aresta *a;

  a = (aresta*) A;
  return a->ponta;
}

char *grafo_calcula_quadrante(Vertice V1, Vertice V2){
  char *final;
  vertice *v1, *v2;

  v1 = (vertice*) V1;
  v2 = (vertice*) V2;
  final = NULL;
  if(v1->x>=v2->x&&v1->y>=v2->y){
    final = malloc(sizeof(char)*4);
    strcpy(final,"sul");
  }
  else if(v1->x<=v2->x&&v1->y>=v2->y){
    final = malloc(sizeof(char)*6);
    strcpy(final,"oeste");
  }
  else if(v1->x>=v2->x&v1->y<=v2->y){
    final = malloc(sizeof(char)*6);
    strcpy(final,"leste");
  }
  else if(v1->x<=v2->x&&v1->y<=v2->y){
    final = malloc(sizeof(char)*6);
    strcpy(final,"norte");
  }
  return final;
}

Vertice grafo_busca_vertice_proximo(Grafo gra, double x, double y){
  int i;
  double dist, distMin, x2, y2;
  vertice *v, *vMin;
  Lista list;
  Posic node, reg;
  grafo *g = (grafo*) gra;
  vMin = NULL;
  distMin = INFINITO;
  for(i=0;i<g->size;i++){
    list = hash_get_position(g->vertices,i);
    node = getFirst(list);
    while(node!=NULL){
      reg = get(list,node);
      v = (vertice*) hash_get_reg(reg);
      dist = distanceBetweenPoints(x,y,v->x, v->y);
      if(dist<distMin){
        distMin = dist;
        vMin = v;
      }
      node = getNext(list,node);
    }
  }
  return vMin;
}
