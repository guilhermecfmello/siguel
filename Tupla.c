#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tupla.h"


typedef struct _tupla{
  double x;
  double y;
}tupla;

Tupla tuplas_create(){
  int i;
  tupla *t;
  t = (tupla*) malloc(sizeof(tupla)*11);
  for(i=0;i<11;i++){
    t[i].x = 0;
    t[i].y = 0;
  }
  return t;
}

int tuplas_verifica_regs(char *registrador){
  if(strcmp(registrador,"R0")==0)
    return 0;
  else if(strcmp(registrador,"R1")==0)
    return 1;
  else if(strcmp(registrador,"R2")==0)
    return 2;
  else if(strcmp(registrador,"R3")==0)
    return 3;
  else if(strcmp(registrador,"R4")==0)
    return 4;
  else if(strcmp(registrador,"R5")==0)
    return 5;
  else if(strcmp(registrador,"R6")==0)
    return 6;
  else if(strcmp(registrador,"R7")==0)
    return 7;
  else if(strcmp(registrador,"R8")==0)
    return 8;
  else if(strcmp(registrador,"R9")==0)
    return 9;
  else if(strcmp(registrador,"R10")==0)
    return 10;
  else return -1;
}

void tuplas_set_regs(Tupla T, char *registrador, double x, double y){
  int i;
  tupla *t;

  t = (tupla*) T;
  i = tuplas_verifica_regs(registrador);
  if(i>=0){
    t[i].x = x;
    t[i].y = y;
  }
  else{
    printf("\nErro ao setar registradores");
  }
}

double tuplas_get_x(Tupla T, char *registrador){
  int i;
  tupla *t;
  t = (tupla*) T;
  i = tuplas_verifica_regs(registrador);
  return t[i].x;
}

double tuplas_get_y(Tupla T, char *registrador){
  int i;
  tupla *t;
  t = (tupla*) T;
  i = tuplas_verifica_regs(registrador);
  return t[i].y;
}
