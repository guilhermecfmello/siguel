#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estabelecimento.h"

typedef struct _estab{
  char *cnpj;
  char *nome;
  char *codt;
  char *cep;
  char face;
  int num;
}estab;

Estab estab_create(char *cnpj, char *nome, char *codt,char *cep, char face, int num){
  estab *est;
  est = malloc(sizeof(estab));
  est->cnpj = malloc(sizeof(char)*(strlen(cnpj)+1));
  est->nome = malloc(sizeof(char)*(strlen(nome)+1));
  est->codt = malloc(sizeof(char)*(strlen(codt)+1));
  est->cep = malloc(sizeof(char)*(strlen(cep)+1));
  est->face = face;
  est->num = num;
  strcpy(est->cnpj,cnpj);
  strcpy(est->nome,nome);
  strcpy(est->codt,codt);
  strcpy(est->cep,cep);
  return est;
}

char *estab_get_cnpj(Estab est){
  estab *e = (estab*) est;
  return e->cnpj;
}

char *estab_get_nome(Estab est){
  estab *e = (estab*) est;
  return e->nome;
}

char *estab_get_codt(Estab est){
  estab *e = (estab*) est;
  return e->codt;
}

char *estab_get_cep(Estab est){
  estab *e = (estab*) est;
  return e->cep;
}

char estab_get_face(Estab est){
  estab *e = (estab*) est;
  return e->face;
}

int estab_get_num(Estab est){
  estab *e = (estab*) est;
  return e->num;
}
