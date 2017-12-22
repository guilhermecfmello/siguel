#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Semaforo.h"

typedef struct _semaforo{
  double x;
  double y;
  double tempo;
  char *id;
}semaforo;

Semaforo createSemaforo(double x, double y, char *id){
  int size;
  char *newId = NULL;
  semaforo *s = (semaforo*)malloc(sizeof(semaforo));
  s->x = x;
  s->y = y;
  s->tempo = 0;
  size = strlen(id);
  newId = malloc(sizeof(char)*(size+1));
  strcpy(newId,id);
  s->id = newId;
  return s;
}

double getSemaforoX(Semaforo sem){
  semaforo *s = (semaforo*) sem;
  return s->x;
}

double getSemaforoY(Semaforo sem){
  semaforo *s = (semaforo*) sem;
  return s->y;
}

char *getSemaforoId(Semaforo sem){
  semaforo *s = (semaforo*) sem;
  return s->id;
}

void getSemaforoInfos(Semaforo sem, double *x, double *y, char **id){
  semaforo *s = (semaforo*) sem;
  *x = s->x;
  *y = s->y;
  *id = s->id;
}

void apagaSemaforoID(Semaforo sem){
  semaforo *s = (semaforo*) sem;
  free(s->id);
}

void setSemaforoTempo(Semaforo sem, double tempo){
  semaforo *s;
  if(sem!=NULL){
    s = (semaforo*) sem;
    s->tempo = tempo;
  }
}
