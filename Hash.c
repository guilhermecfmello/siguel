#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "Lista.h"

typedef struct _hash{
  int size;
  Lista *vector;
}hash;

typedef struct _reg{
  PosicH content;
  char* key;
}reg;

Lista hash_get_position(Hash ha, int position){
  hash *h = (hash*) ha;
  return h->vector[position];
}

int hash_get_size(Hash ha){
  hash *h = (hash*) ha;
  return h->size;
}

PosicH hash_search_List(Hash ha, char* key){
  int ind;
  Posic aux;
  reg *r;
  hash *h = (hash*) ha;
  ind = hash_code(ha,key);
  if(ind<0){
    printf("Erro na funcao hash\n");
    return NULL;
  }
  else{
    aux = getFirst(h->vector[ind]);
    if(aux!=NULL){
      r = (reg*)get(NULL,aux);
      while(strcmp(r->key,key)!=0){
        aux = getNext(NULL,aux);
        if(aux==NULL)
          break;
        r = (reg*)get(NULL,aux);
      }
      return aux;
    }
    else{
      return NULL;
    }
  }
}

Hash hash_remove(Hash ha, char* key){
  int ind;
  PosicH p;
  hash *h = (hash*) ha;
  ind = hash_code(ha,key);
  p = hash_search_List(ha,key);
  if(p!=NULL){
    remover(h->vector[ind], p);
  }
}

RegH hash_search(Hash ha, char* key){
  int ind;
  PosicH p;
  reg *r;
  ind = hash_code(ha,key);
  p = hash_search_List(ha,key);
  if(p!=NULL){
    r = (reg*) get(NULL,p);
    return r->content;
  }
  else
    return NULL;
}



RegH hash_insert(Hash ha, PosicH content, char* key){
  int ind;
  reg *r;
  hash *h = (hash*) ha;
  ind = hash_code(h,key);
  if(ind>=0){
    r = malloc(sizeof(reg));
    if(r!=NULL){
      r->content = content;
      r->key = key;
      insert(h->vector[ind],r);
      return r;
    }else{
      printf("Erro na inclusao do objeto na tabela hash\n");
      return NULL;
    }

  }else{
    printf("Erro na geracao da chave na tabela Hash\n");
    return NULL;
  }
}

int hash_code(Hash ha, char* key){
  int size, i, ind;
  char transform[42];
  hash *h = (hash*) ha;
  strcpy(transform,"euvounorockeuvounofunkehhip-hopatitudepunk");
  ind = 0;
  if(key!=NULL){
    size = strlen(key);
    for(i=0;i<size;i++){
      ind += key[i]*transform[i];
    }
    ind = ind % h->size;
    return ind;
  }
  else{
    return -1;
  }
}

Hash createHash(int size){
  int i;
  hash *h;
  h = malloc(sizeof(hash));
  h->size = size;
  h->vector = malloc(sizeof(Lista)*size);
  for(i=0;i<size;i++)
    h->vector[i] = createList();
  return h;
}

PosicH hash_get_reg(RegH node){
  reg *r = (reg*) node;
  return r->content;
}

/*FUNCOES TESTE, EXCLUI-LAS ANTES DE ENTREGAR O TRABALHO*/

void imprimeTeste(Hash ha){
  int i;
  char *aux, *aux2;
  Posic p;
  reg *r;
  hash *h = (hash*) ha;
  for(i=0;i<h->size;i++){
    p = getFirst(h->vector[i]);
    while(p!=NULL){
      r = (reg*) get(NULL,p);
      aux = r->content;
      aux2 = r->key;
      p = getNext(NULL,p);
    }
  }
}

char *getKey(Hash ha, RegH re){
  reg *r = (reg*) re;
  return r->key;
}

char *getContent(Hash ha, RegH re){
  reg *r = (reg*) re;
  return r->content;
}
