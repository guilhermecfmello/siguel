#include <stdio.h>
#include <stdlib.h>
#include "Conversao.h"
#include "ConvexHull.h"
#include "Ordenacao.h"
#include "Pilha.h"
#include "Lista.h"
#include "Quadtree.h"
#include "Operacoes.h"

Tree criaQuadTree(Pilha ch){
  int i;
  double x, y;
  vectorNode *v;
  Tree newTree;
  Posic item;
  newTree = NULL;
  if(getSizePilha(ch)>0){
    newTree = quadtree_create();
    for(i=getSizePilha(ch);i>0;i--){
      v = pop(ch);
      quadtree_add(newTree, v->ptr, v->x, v->y);
    }
  }
    return newTree;
}

Cidade listToQuadTreeCH(Cidade cid){
  int i;
  double x, y;
  getX gx;
  getY gy;
  Pilha ch;
  Posic item;
  Tree newTree;
  vectorNode *v;
  newTree = NULL;

  gx = &getQuadraX;
  gy = &getQuadraY;
  ch = convexHull(getQuadrasList(cid),gx,gy);
  newTree = criaQuadTree(ch);
  /*newTree = listToQuadtree(getQuadrasList(cid), gx,gy);*/
  setQuadrasQuadTree(cid,newTree);


  gx = &getSemaforoX;
  gy = &getSemaforoY;
  ch = convexHull(getSemaforosList(cid),gx,gy);
  newTree = criaQuadTree(ch);
  setSemaforosQuadTree(cid, newTree);

  gx = &getHidranteX;
  gy = &getHidranteY;
  ch = convexHull(getHidrantesList(cid),gx,gy);
  newTree = criaQuadTree(ch);
  setHidrantesQuadTree(cid,newTree);

  gx = &getTorreX;
  gy = &getTorreY;
  ch = convexHull(getTorresList(cid), gx, gy);
  newTree = criaQuadTree(ch);
  setTorresQuadTree(cid, newTree);
  return cid;
}
