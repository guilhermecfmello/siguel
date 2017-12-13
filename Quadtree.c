#include <stdio.h>
#include <stdlib.h>
#include "Quadtree.h"

typedef struct _node{
  double x;
  double y;
  Posic nw;
  Posic ne;
  Posic sw;
  Posic se;
  Content content;
}node;

typedef struct _head{
  int size;
  int height;
  node *root;
}head;

Tree quadtree_create(){
  head *h = malloc(sizeof(head));
  h->size = 0;
  h->height = 0;
  h->root = NULL;
  return h;
}

void quadtree_recursiveAdd(Tree t, Posic p){
  node *n1;
  if(p!=NULL){
    n1 = (node*) p;
    quadtree_recursiveAdd(t, n1->nw);
    quadtree_recursiveAdd(t, n1->ne);
    quadtree_recursiveAdd(t, n1->sw);
    quadtree_recursiveAdd(t, n1->se);
    quadtree_add(t,n1->content,n1->x,n1->y);
    free(n1);
  }
}

Posic quadtree_getSomeNode(Tree t, Posic p){
  node *n;
  n = (node*) p;
  if(n->nw!=NULL) return n->nw;
  else if(n->ne!=NULL) return n->ne;
  else if(n->sw!=NULL) return n->sw;
  else if(n->se!=NULL) return n->se;
  else return NULL;
}

Posic quadtree_add(Tree t, Content c, double x, double y){
  node *n, *aux, *bef;
  int op, down;
  head *tree = (head*) t;
  n = malloc(sizeof(node));
  down = 0;
  n->x = x;
  n->y = y;
  n->nw = NULL;
  n->ne = NULL;
  n->sw = NULL;
  n->se = NULL;
  n->content = c;
  if(tree->root!=NULL){
    aux = tree->root;
    while(aux!=NULL){
      down++;
      op = quadtree_compareQuad(aux,n);
      bef = aux;
      switch (op) {
        case 1:
          aux = aux->nw;
          break;
        case 2:
          aux = aux->ne;
          break;
        case 3:
          aux = aux->sw;
          break;
        case 4:
          aux = aux->se;
          break;
        default:
          aux = NULL;
          break;
      }
    }
    switch(op){
      case 1:
        bef->nw = n;
        tree->size++;
        if(down>tree->height)
          tree->height = down;
        break;
      case 2:
        bef->ne = n;
        tree->size++;
        if(down>tree->height)
          tree->height = down;
        break;
      case 3:
        bef->sw = n;
        tree->size++;
        if(down>tree->height)
          tree->height = down;
        break;
      case 4:
        bef->se = n;
        tree->size++;
        if(down>tree->height)
          tree->height = down;
        break;
      default:
        printf("\n***CONTEUDO NAO INCLUIO NA ARVORE***\n");
        break;
    }
  }
  else{
    tree->root = n;
    tree->size++;
  }
  return n;
}

int quadtree_compareQuad(Posic p1, Posic p2){
  node *n1, *n2;
  n1 = (node*) p1;
  n2 = (node*) p2;
  if(n2->x<=n1->x && n2->y<= n1->y) return 4;
  else if(n2->x >= n1->x && n2->y <= n1->y) return 3;
  else if(n2->x <= n1->x && n2->y >= n1->y) return 2;
  else if(n2->x >= n1->x && n2->y >= n1->y) return 1;
  else return -1;
}

Posic quadtree_getRoot(Tree t){
  head *h = (head*) t;
  return h->root;
}

Content quadtree_get(Posic p){
  node *n = (node*) p;
  return n->content;
}

Posic quadtree_getNodeNW(Tree t, Posic p){
  node *n = (node*) p;
  return n->nw;
}

Posic quadtree_getNodeNE(Tree t, Posic p){
  node *n = (node*) p;
  return n->ne;
}

Posic quadtree_getNodeSW(Tree t, Posic p){
  node *n = (node*) p;
  return n->sw;
}

Posic quadtree_getNodeSE(Tree t, Posic p){
  node *n = (node*) p;
  return n->se;
}

int quadtree_getHeight(Tree t){
  head *h = (head*) t;
  return h->height;
}

int quadtree_getSize(Tree t){
  head *h = (head*) t;
  return h->size;
}

void quadtree_resetNW(Tree t, Posic p){
  node *n = (node*) p;
  n->nw = NULL;
}
void quadtree_resetNE(Tree t, Posic p){
  node *n = (node*) p;
  n->ne = NULL;
}
void quadtree_resetSW(Tree t, Posic p){
  node *n = (node*) p;
  n->sw = NULL;
}
void quadtree_resetSE(Tree t, Posic p){
  node *n = (node*) p;
  n->se = NULL;
}

int quadtree_isLeaf(Tree t, Posic p){
  node *n = (node*) p;
  if(n->nw==NULL && n->ne==NULL && n->sw==NULL && n->se==NULL) return 1;
  else return 0;
}

int quadtree_remove(Tree t, Posic p){
  int quad;
  int *teste1, *teste2;
  Posic down, aux2;
  node *find, *aux, *end;
  head *h;
  find = (node*) p;
  down = quadtree_getRoot(t);
  h = (head*) t;
  /*SE O NO A SER REMOVIDO FOR A RAIZ*/
  if(down==find){
    end = (node*) down;
    aux2 = quadtree_getSomeNode(t,down);
    h->root = aux2;
    if(aux2!=end->nw) quadtree_recursiveAdd(t,end->nw);
    if(aux2!=end->ne) quadtree_recursiveAdd(t,end->ne);
    if(aux2!=end->sw) quadtree_recursiveAdd(t,end->sw);
    if(aux2!=end->se) quadtree_recursiveAdd(t,end->se);
  }
  /*SE O NO A SER REMOVIDO SEJA QUALQUER*/
  else{
    while(down!=find&&down!=NULL){
      aux = down;
      down = quadtree_down(t, down, find);
    }
    teste1 = quadtree_get(aux);
    teste2 = quadtree_get(down);
    printf("Teste aux: %d down: %d\n", *teste1,*teste2);
    quad = quadtree_compareQuad(aux,down);
    if(quad==1) aux->nw = NULL;
    else if(quad==2) aux->ne = NULL;
    else if(quad==3) aux->sw = NULL;
    else if(quad==4) aux->se = NULL;
    end = (node*) down;
    quadtree_recursiveAdd(t,end->nw);
    quadtree_recursiveAdd(t,end->ne);
    quadtree_recursiveAdd(t,end->sw);
    quadtree_recursiveAdd(t,end->se);
  }
  h->size--;
}


Posic quadtree_down(Tree t, Posic p1, Posic p2){
  int quad;
  if(p1 !=NULL && p2 != NULL){
    quad = quadtree_compareQuad(p1,p2);
    if(quad==1) return quadtree_getNodeNW(t, p1);
    else if(quad==2) return quadtree_getNodeNE(t, p1);
    else if(quad==3) return quadtree_getNodeSW(t, p1);
    else if(quad==4) return quadtree_getNodeSE(t, p1);
    else return NULL;
  }
  return NULL;
}
/*FUNCOES PARA EXCLUIR ABAIXO - APENAS PARA TESTE*/
void quadtree_print(Posic p){
  int *i;
  node *n;
  if(p!=NULL){
    i = quadtree_get(p);
    printf(">%d \n", *i);
    n = (node*) p;
    quadtree_print(n->nw);
    quadtree_print(n->ne);
    quadtree_print(n->sw);
    quadtree_print(n->se);
  }

}
