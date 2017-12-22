#include "Pilha.h"

typedef struct _posic{
  PosicP element;
  Pilha next;
}posic;

typedef struct _pilha{
  PosicP first;
  int size;
}pilha;

Pilha createPilha(){
  pilha *p = (pilha*) malloc(sizeof(pilha));
  p->first = NULL;
  p->size = 0;
}

void push(Pilha pil, PosicP elemento){
  pilha *p = (pilha*) pil;
  posic *po = (posic*)malloc(sizeof(posic));
  po->element = elemento;
  if(p->first==NULL){
    po->next = NULL;
    p->first = po;
  }
  else{
    po->next = p->first;
    p->first = po;
  }
  p->size++;
}

PosicP pop(Pilha pil){
  pilha *pilhaHead = (pilha*) pil;
  posic *aux;
  PosicP elementNode;
  if(pilhaHead->size>1){
    aux = pilhaHead->first;
    elementNode = aux->element;
    pilhaHead->first = aux->next;
    pilhaHead->size--;
    free(aux);
    return elementNode;
  }
  else if(pilhaHead->size==1){
    aux = pilhaHead->first;
    elementNode = aux->element;
    pilhaHead->size--;
    free(aux);
    pilhaHead->first = NULL;
    return elementNode;
  }
  else{
    return NULL;
  }
}

PosicP topPilha(Pilha pil){
  pilha *p = (pilha*) pil;
  posic *aux = NULL;
  if(pil!=NULL){
    if(p->size>0){
      aux = p->first;
      return aux->element;
    }
    else
      return NULL;
  }
  return NULL;
}

PosicP nextTopPilha(Pilha pil){
  pilha *p = (pilha*) pil;
  posic *aux = NULL;
  if(pil!=NULL){
    if(p->size>1){
      aux = p->first;
      aux = aux->next;
      return aux->element;
    }
    else
      return NULL;
  }
  return NULL;
}

int getSizePilha(Pilha pil){
  pilha *p = (pilha*) pil;
  return p->size;
}
