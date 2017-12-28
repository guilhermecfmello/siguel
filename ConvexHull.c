#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ConvexHull.h"
#include "Ordenacao.h"
#include "Quadra.h"

vectorNode *listToVector(Lista l, getX gx, getY gy){
  int size, i;
  PosicP aux, aux2;
  vectorNode *v = NULL;
  aux = getFirst(l);
  size = length(l);
  if(aux!=NULL){
    v = malloc(sizeof(vectorNode)*size);
    for(i=0;i<size;i++){
      aux2 = get(l,aux);
      v[i].ptr = aux2;
      v[i].x = gx(aux2);
      v[i].y = gy(aux2);
      v[i].ang = -1;
      aux = getNext(l,aux);
    }
  }
  /*printf("\nTESTANDO TRANSFORMACAO LISTA PARA VETOR: %f %f", v[i-1].x, v[i-1].y);*/
  return v;
}

void calculaAngulos(vectorNode *vector, int size){
  int i;
  double x1, y1, x2, y2;
  if(size>1){
    x1 = vector[0].x;
    y1 = vector[0].y;
    for(i=1;i<size;i++){
      x2 = vector[i].x;
      y2 = vector[i].y;
      vector[i].ang = atan2((y2-y1),(x2-x1));
    }
  }
}

void iniciaVetor(vectorNode *vector, int size){
  int i, j, indiceMenor;
  double refY, refX;
  if(size>0){
    refY = vector[0].y;
    refX = vector[0].x;
    indiceMenor = 0;
    for(i=0;i<size;i++){
      if(vector[i].y<refY){
        indiceMenor = i;
        refY = vector[i].y;
        refX = vector[i].x;
      }
      else if(vector[i].y==refY){
        if(vector[i].x<refX){
          indiceMenor = i;
          refY = vector[i].y;
          refX = vector[i].x;
        }
      }
    }
    swap(vector,indiceMenor,0);
  }
}


Pilha transfereToPilha(vectorNode *vector, int size){
  int i;
  Pilha p;
  Posic aux;
  p = NULL;
  if(size>0){
    p = createPilha();
    for(i=1;i<size;i++){
      push(p,&vector[i]);
    }
  }
  return p;
}

vectorNode *stackToVector(Pilha p, int *size){
  int i;
  Pilha auxP;
  vectorNode *aux, *newVector;
  *size = getSizePilha(p);
  newVector = malloc(sizeof(vectorNode)*(*size));
  for(i=0;i<(*size);i++){
    auxP = pop(p);
    aux = (vectorNode*) auxP;
    newVector[i].x = aux->x;
    newVector[i].y = aux->y;
    newVector[i].ang = aux->ang;
    newVector[i].ptr = aux->ptr;
  }
  return newVector;
}


void arrumaIntervaloAngulosIguais(vectorNode *vector, int i, int j){
  int aux;
  double x;
  x = vector[i].x;
  aux = i;
  for(aux = i + 1;aux<=j;aux++){
    if(vector[i].x<x){
      swap(vector, i, j);
      i = aux;
    }
  }

}

void arrumaAngulosIguais(vectorNode *vector, int size){
  int i, j;
  for(i=0;i<size-1;i++){
    if(vector[i].ang==vector[i+1].ang){
      j = 1;
      while(vector[i+j].ang==vector[i+j].ang){
        if(i+j>size-2)
          break;
        j++;
      }
      arrumaIntervaloAngulosIguais(vector,i,i+j);
      i = i + j - 1;
    }
  }

}

Pilha calculaConvexHull(vectorNode *vector, int size, Pilha ch, Pilha inside){
  int i;
  Pilha aux;
  Posic p, c;
  if(size<3)
    return NULL;
  if(size>2){
    push(ch,&vector[0]);
    push(ch,&vector[1]);
    push(ch,&vector[2]);
    for(i=3;i<size;i++){
      p = nextTopPilha(ch);
      c = topPilha(ch);
      while(ccw(p,c,&vector[i])>0){
        push(inside,pop(ch));
        p = nextTopPilha(ch);
        c = topPilha(ch);
      }
      push(ch,&vector[i]);
    }
  }
  return ch;
}

Pilha convexHull(Lista l, getX gx, getY gy){
  Pilha inside, ch, aux;
  int i, size;
  vectorNode *vector;
  size = length(l);
  if(size<3)
    return NULL;
  vector = listToVector(l,gx,gy);
  iniciaVetor(vector, size);
  calculaAngulos(vector, size);
  quicksort(vector,1,size-1);
  arrumaAngulosIguais(vector,size);
  inside = createPilha();
  ch = createPilha();
  do{
    calculaConvexHull(vector,size,ch,inside);
    vector = stackToVector(inside,&size);
  }while(size>2);
  for(i=0;i<size;i++)
    push(ch,&vector[i]);
  return ch;
}
/*for(i=3;i<size;i++){
c = topPilha(ch);
push(inside,pop(ch));
while(ccw(topPilha(ch),c,&vector[i])!=-1){
c = topPilha(ch);
push(inside,pop(ch));
if(topPilha(ch)==NULL)
printf("\nvector[i].x: %f vector[i].y: %f", vector[i].x, vector[i].y);
}
push(ch,c);
push(ch,&vector[i]);
}
*/


double ccw(vectorNode *v1, vectorNode *v2, vectorNode *v3){
  double aux1;
  aux1 = (v2->x - v1->x)*(v3->y-v1->y) - (v2->y - v1->y)*(v3->x - v1->x);
  if(aux1>0) return -1;
  else if(aux1<0) return 1;
  else return 0;
}
