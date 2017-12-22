#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hidrante.h"

typedef struct _hidrante{
  double x;
  double y;
  double vazao;
  char *id;
}hidrante;

Hidrante createHidrante(double x, double y, char *id){
  int size;
  char *newId;
  hidrante *h = (hidrante*) malloc(sizeof(hidrante));
  h->x = x;
  h->y = y;
  h->vazao = 0;
  size = strlen(id);
  newId = malloc(sizeof(char)*(size+1));
  strcpy(newId,id);
  h->id = newId;
  return h;
}

double getHidranteX(Hidrante hid){
  hidrante *h =  (hidrante*) hid;
  return h->x;
}

double getHidranteY(Hidrante hid){
  hidrante *h =  (hidrante*) hid;
  return h->y;
}

char *getHidranteId(Hidrante hid){
  hidrante *h =  (hidrante*) hid;
  return h->id;
}

void getHidranteInfos(Hidrante hid, double *x, double *y, char **id){
  hidrante *h = (hidrante*) hid;
  *x = h->x;
  *y = h->y;
  *id = h->id;
}

void apagaHidranteID(Hidrante hid){
  hidrante *h = (hidrante*) hid;
  free(h->id);
}

void setHidranteVazao(Hidrante hid, double vazao){
  hidrante *h;
  if(hid!=NULL){
    h = (hidrante*) hid;
    h->vazao = vazao;
  }
}
