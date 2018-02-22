#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dicionario.h"


#define SIZE 31
typedef struct _dic{
    PosicH cpfXpessoa;/*Dado o cpf, retorna a pessoa*/
    PosicH numcelXpessoa;/*Dado num. celular, retorna a pessoa que usa esse numero*/
    PosicH numcelXradiobase;/*Dado num. celular, retorna a radiobase em que o celular esta conectado.*/
    PosicH codtestXest;/*Dado o codt do estabel. retorna o estabelecimento*/
    PosicH codtestXdesc;/*Dado o codt do estabel., retorna a descricao dele*/
    PosicH cepXquadra;/*Dado o cep, retorna dados da quadra.*/
    PosicH umnumcelXpessoa; /*Dado o numero de telefone, retorna o cpf da pessoa com
base na chave telefone, caso ela seja cliente da UelMobile*/
    PosicH sunumcelXpessoa;/*Dado o numero de telefone, retorna o cpf da pessoa com
base na chave telefone, caso ela seja cliente da SERCOMTUEL*/
    PosicH umidXtorre;
    /*Dado o id, busca na empresa uelmobile a torre deste id*/
    PosicH suidXTorre;
    /*Dado o id, busca na empresa sercomtuel a torre deste id*/
}dic;

Hash getHash(Dicionario di, char *type){
  dic *d = (dic*) di;
  if(strcmp(type,"cpfXpessoa")==0)
  return d->cpfXpessoa;
  else if (strcmp(type,"numcelXpessoa")==0)
  return d->numcelXpessoa;
  else if(strcmp(type,"numcelXradiobase")==0)
  return d->numcelXradiobase;
  else if(strcmp(type,"codtestXest")==0)
  return d->codtestXest;
  else if(strcmp(type,"cepXquadra")==0)
  return d->cepXquadra;
  else if(strcmp(type,"umnumcelXpessoa")==0)
  return d->umnumcelXpessoa;
  else if(strcmp(type,"sunumcelXpessoa")==0)
  return d->sunumcelXpessoa;
  else if(strcmp(type,"codtestXdesc")==0)
  return d->codtestXdesc;
  else if(strcmp(type,"umidXtorre")==0)
  return d->umidXtorre;
  else if(strcmp(type,"suidXTorre")==0)
  return d->suidXTorre;
  else
  return NULL;
}



Dicionario dicionario_create(){
  dic *d;
  d = malloc(sizeof(dic));
  d->cpfXpessoa = createHash(SIZE);
  d->numcelXpessoa = createHash(SIZE);
  d->numcelXradiobase = createHash(SIZE);
  d->codtestXest = createHash(SIZE);
  d->cepXquadra = createHash(SIZE);
  d->umnumcelXpessoa = createHash(SIZE);
  d->sunumcelXpessoa = createHash(SIZE);
  d->codtestXdesc = createHash(SIZE);
  d->umidXtorre = createHash(SIZE);
  d->suidXTorre = createHash(SIZE);
}

void dicio_insere_pessoaCpf(Dicionario di, Pessoa p){
  char *key, *aux;
  dic *d = (dic*) di;
  aux = pessoa_get_cpf(p);
  key = malloc(sizeof(char)*strlen(aux)+1);
  strcpy(key,aux);
  hash_insert(d->cpfXpessoa,p,key);
}

void dicio_insere_pessoaNumCel(Dicionario di, Pessoa p){
  Telefone tel;
  dic *d = (dic*) di;
  tel = pessoa_get_tel(p);
  hash_insert(d->numcelXpessoa,p,telefone_get_num(tel));

}

void dicio_insere_radiobaseNumCel(Dicionario di, char *torre, char *num){
  char *n, *tor;
  dic *d = (dic*) di;
  n = malloc(sizeof(char)*(strlen(num)+1));
  tor = malloc(sizeof(char)*(strlen(torre)+1));
  strcpy(n,num);
  strcpy(tor,torre);
  hash_insert(d->numcelXradiobase,tor,n);
}

void dicio_insere_Desctype(Dicionario di, char *desc, char *type){
  char *descri, *t;
  dic *d = (dic*) di;
  descri = malloc(sizeof(char)*(strlen(desc)+1));
  t = malloc(sizeof(char)*(strlen(type)+1));
  strcpy(descri,desc);
  strcpy(t,type);
  hash_insert(d->codtestXdesc,descri,t);
}

void dicio_insere_quadraCep(Dicionario di, Quadra qua){
  dic *d = (dic*) di;
  hash_insert(d->cepXquadra,qua,getQuadraCep(qua));
}

Pessoa dicio_searchPessoa_cpf(Dicionario di, char *key){
  Pessoa p;
  dic *d = (dic*) di;
  p = hash_search(d->cpfXpessoa,key);
  return p;
}

Pessoa dicio_searchPessoa_numcel(Dicionario di, char *key){
  Pessoa p;
  dic *d = (dic*) di;
  p = hash_search(d->numcelXpessoa,key);
  return p;
}

char *dicio_searchRadio_numcel(Dicionario di, char *key){
  Torre t;
  dic *d = (dic*) di;
  t = hash_search(d->numcelXradiobase,key);
  return t;
}

char *dicio_searchDesc_type(Dicionario di, char *key){
  char *c;
  dic *d = (dic*) di;
  c = hash_search(d->codtestXdesc,key);
  return c;
}

Quadra dicio_search_Quadra_cep(Dicionario di, char *key){
  Quadra q;
  dic *d = (dic*) di;
  q = hash_search(d->cepXquadra,key);
  return q;
}

void dicio_insere_estType(Dicionario di, Estab est, char *key){
  char *c;
  dic *d = (dic*) di;
  c = malloc(sizeof(char)*(strlen(key)+1));
  strcpy(c,key);
  hash_insert(d->codtestXest,est,c);
}

Estab dicio_search_Estab_type(Dicionario di, char *key){
  Estab est;
  dic *d = (dic*) di;
  est = hash_search(d->codtestXest,key);
  return est;
}

void dicio_insere_cpf_sercomtuel(Dicionario di, char *cpf, char *num){
  char *c, *n;
  dic *d = (dic*) di;
  c = malloc(sizeof(char)*(strlen(cpf)+1));
  n = malloc(sizeof(char)*(strlen(num)+1));
  strcpy(c,cpf);
  strcpy(n,num);
  hash_insert(d->sunumcelXpessoa,c,n);
}

void dicio_insere_cpf_uelmobile(Dicionario di, char *cpf, char *num){
  char *c, *n;
  dic *d = (dic*) di;
  c = malloc(sizeof(char)*(strlen(cpf)+1));
  n = malloc(sizeof(char)*(strlen(num)+1));
  strcpy(c,cpf);
  strcpy(n,num);
  hash_insert(d->umnumcelXpessoa,c,n);
}

char *dicio_search_cpf_sercomtuel(Dicionario di, char *num){
  dic *d = (dic*) di;
  return hash_search(d->sunumcelXpessoa,num);
}

char *dicio_search_cpf_uelmobile(Dicionario di, char *num){
  dic *d = (dic*) di;
  return hash_search(d->umnumcelXpessoa,num);
}

void dicio_insere_torre_sercomtuel(Dicionario di, Torre tor){
  dic *d = (dic*) di;
  hash_insert(d->suidXTorre,tor,getTorreId(tor));
}

void dicio_insere_torre_uelmobile(Dicionario di, Torre tor){
  char *id;
  dic *d = (dic*) di;
  id = getTorreId(tor);
  hash_insert(d->umidXtorre,tor,id);
}

Torre dicio_search_torre_sercomtuel(Dicionario di, char *id){
  dic *d = (dic*) di;
  return hash_search(d->suidXTorre,id);
}

Torre dicio_search_torre_uelmobile(Dicionario di, char *id){
  dic *d = (dic*) di;
  return hash_search(d->umidXtorre,id);
}

void dicio_remove_radio_numcel(Dicionario di, char *key){
  dic *d = (dic*) di;
  hash_remove(d->numcelXradiobase,key);
}
