#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Torre.h"

typedef struct _torre{
  double x;
  double y;
  double raio;
  char *id;
  char operadora;
}torre;

Torre createTorre(double x, double y, char *id){
  char *newId;
  torre *t = (torre*) malloc(sizeof(torre));
  newId = malloc(sizeof(char)*(strlen(id)+1));
  strcpy(newId,id);
  t->x = x;
  t->y = y;
  t->id = newId;
  t->raio = 0;
  t->operadora = 'n';
  return t;
}

void setTorreOperadora(Torre tor, char op){
  torre *t;
  t = (torre*) tor;
  t->operadora = op;
}
char getTorreOperadora(Torre tor){
  torre *t = (torre*) tor;
  return t->operadora;
}


double getTorreX(Torre tor){
  torre *t = (torre*) tor;
  return t->x;
}

double getTorreY(Torre tor){
  torre *t = (torre*) tor;
  return t->y;
}

char *getTorreId(Torre tor){
  torre *t = (torre*) tor;
  return t->id;
}

void getTorreInfos(Torre tor, double *x, double *y, char **id){
  torre *t = (torre*) tor;
  *x = t->x;
  *y = t->y;
  *id = t->id;
}

void apagaTorreID(Torre tor){
  torre *t = (torre*) tor;
  free(t->id);
}

void setTorreRaio(Torre tor, double r){
  torre *t;
  if(tor!=NULL){
    t = (torre*) tor;
    t->raio = r;
  }
}

double getTorreRaio(Torre tor){
  torre *t;
  if(tor!=NULL){
    t = (torre*) tor;
    return t->raio;
  }
}
