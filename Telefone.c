#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Telefone.h"

typedef struct _telefone{
  char *num;
  char *radiobase;
}telefone;

Telefone telefone_create(char *num, char *radiobase){
  telefone *t = malloc(sizeof(telefone));
  t->num = malloc(sizeof(char)*(strlen(num)+1));
  t->radiobase = malloc(sizeof(char)*(strlen(radiobase)+1));
  strcpy(t->num,num);
  strcpy(t->radiobase,radiobase);
  return t;
}

char *telefone_get_num(Telefone tel){
  telefone *t = (telefone*) tel;
  return t->num;
}

char *telefone_get_radiobase(Telefone tel){
  telefone *t = (telefone*) tel;
  return t->radiobase;
}

void telefone_set_num(Telefone tel, char *num){
  telefone *t = (telefone*) tel;
  t->num = malloc(sizeof(char)*(strlen(num)+1));
  strcpy(t->num,num);
}

void telefone_set_radiobase(Telefone tel, char *radiobase){
  telefone *t = (telefone*) tel;
  t->radiobase = malloc(sizeof(char)*(strlen(radiobase)+1));
  strcpy(t->radiobase,radiobase);
}
