#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Quadra.h"

typedef struct _quadra{
  double x;
  double y;
  double w;
  double h;
  char *cep;
}quadra;

int comparaTeste(Quadra pq1, Quadra pq2, Quadra pq3){
  quadra *q1, *q2, *q3;
  q1 = (quadra*) pq1;
  q2 = (quadra*) pq2;
  if(pq3!=NULL){
    q3 = (quadra*) pq3;
    return 0;
  }
  else{
    if(q1->x>=q2->x) return 1;
  }
  return 0;
}

Quadra createQuadra(double x, double y, double w, double h, char *end){
  quadra *q = (quadra*)malloc(sizeof(quadra));
  char *aux = NULL;
  int size;
  size = strlen(end);
  aux = malloc(sizeof(char)*(size+1));
  strcpy(aux,end);
  q->x = x;
  q->y = y;
  q->w = w;
  q->h = h;
  q->cep = aux;
  return q;
}

double getQuadraX(Quadra qua){
  quadra *q = (quadra*) qua;
  return q->x;
}

double getQuadraY(Quadra qua){
  quadra *q = (quadra*) qua;
  return q->y;
}

double getQuadraW(Quadra qua){
  quadra *q = (quadra*) qua;
  return q->w;
}

double getQuadraH(Quadra qua){
  quadra *q = (quadra*) qua;
  return q->h;
}

char *getQuadraCep(Quadra qua){
  quadra *q = (quadra*) qua;
  return q->cep;
}

void getQuadraInfos(Quadra qua, double *x, double *y, double *w, double *h, char **end){
  quadra *q = (quadra*) qua;
  *x = q->x;
  *y = q->y;
  *w = q->w;
  *h = q->h;
  *end = q->cep;
}

void apagaQuadraCep(Quadra qua){
  quadra *q = (quadra*) qua;
  free(q->cep);
}
