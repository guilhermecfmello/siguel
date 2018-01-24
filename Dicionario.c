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
}

void dicio_insere_pessoaCpf(Dicionario di, Pessoa p){
  dic *d = (dic*) di;
  hash_insert(d->cpfXpessoa,p,(char*)pessoa_get_cpf(p));
}

void dicio_insere_pessoaNumCel(Dicionario di, Pessoa p){
  Telefone tel;
  dic *d = (dic*) di;
  tel = pessoa_get_tel(p);
  hash_insert(d->numcelXpessoa,p,telefone_get_num(tel));
}

void dicio_insere_radiobaseNumCel(Dicionario di, Torre tor, char *num){
  char *n;
  dic *d = (dic*) di;
  n = malloc(sizeof(char)*(strlen(num)+1));
  strcpy(n,num);
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

Torre dicio_searchRadio_numcel(Dicionario di, char *key){
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
