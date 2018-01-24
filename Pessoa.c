#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pessoa.h"

typedef struct _pessoa{
  char *cpf;
  char *nome;
  char *sobrenome;
  char sexo;
  char *nascimento;
  char *cep;
  char *face;
  char *num;
  char *comp;
  Telefone tel;
}pessoa;

Pessoa pessoa_create(char *cpf, char *nome, char *sobrenome,char sexo, char *nasc){
  pessoa *p;
  p = malloc(sizeof(pessoa));
  p->cpf = malloc(sizeof(char)*(strlen(cpf)+1));
  p->nome = malloc(sizeof(char)*(strlen(nome)+1));
  p->sobrenome = malloc(sizeof(char)*(strlen(nome)+1));
  p->nascimento = malloc(sizeof(char)*(strlen(nasc)+1));
  strcpy(p->cpf,cpf);
  strcpy(p->nome,nome);
  strcpy(p->sobrenome,sobrenome);
  strcpy(p->nascimento,nasc);
  p->sexo = sexo;
  p->tel = NULL;
  p->cep = NULL;
  p->face = NULL;
  p->num = NULL;
  p->comp = NULL;
  return p;
}

char *pessoa_get_cpf(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->cpf;
}

char *pessoa_get_nome(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->nome;
}

char *pessoa_get_sobrenome(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->sobrenome;
}

char pessoa_get_sexo(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->sexo;
}

char *pessoa_get_nasc(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->nascimento;
}

Telefone pessoa_get_tel(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->tel;
}

void pessoa_set_tel(Pessoa pes, Telefone tel){
  pessoa *p = (pessoa*) pes;
  p->tel = tel;
}

char *pessoa_get_cep(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->cep;
}

char *pessoa_get_face(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->face;
}

char *pessoa_get_num(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->num;
}

char *pessoa_get_comp(Pessoa pes){
  pessoa *p = (pessoa*) pes;
  return p->comp;
}


void pessoa_set_cep(Pessoa pes, char *set){
  pessoa *p = (pessoa*) pes;
  if(set!=NULL){
    p->cep=malloc(sizeof(char)*(strlen(set)+1));
    strcpy(p->cep,set);
  }
  else
    printf("Erro ao setar cep na pessoa %s\n", p->nome);
}

void pessoa_set_face(Pessoa pes, char *set){
  pessoa *p = (pessoa*) pes;
  if(set!=NULL){
    p->face=malloc(sizeof(char)*(strlen(set)+1));
    strcpy(p->face,set);
  }
  else
    printf("Erro ao setar face na pessoa %s\n", p->nome);
}

void pessoa_set_num(Pessoa pes, char *set){
  pessoa *p = (pessoa*) pes;
  if(set!=NULL){
    p->num=malloc(sizeof(char)*(strlen(set)+1));
    strcpy(p->num,set);
  }
  else
    printf("Erro ao setar num na pessoa %s\n", p->nome);
}

void pessoa_set_comp(Pessoa pes, char *set){
  pessoa *p = (pessoa*) pes;
  if(set!=NULL){
    p->comp=malloc(sizeof(char)*(strlen(set)+1));
    strcpy(p->comp,set);
  }
  else
    printf("Erro ao setar comp na pessoa %s\n", p->nome);
}
