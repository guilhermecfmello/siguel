#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

typedef struct forma{
  struct forma2 *first;
  struct forma2 *last;
  int size;
}head;

typedef struct forma2{
  struct forma2 *next;
  struct forma2 *prev;
  Item content;
}posic;


Lista createList(){
  head *newList = (head*)malloc(sizeof(head));
  newList->first = NULL;
  newList->last = NULL;
  newList->size = 0;
  return (Lista)newList;
}

int length(Lista list){
  head *aux = (head*)list;
  return aux->size;
}

Posic insert(Lista list, Lista item){
  head *l = (head*) list;
  posic *newNode = (posic*) malloc(sizeof(posic));
  posic *aux = (posic*)l->last;
  newNode->next = NULL;
  newNode->prev = aux;
  newNode->content = item;
  l->size++;
  l->last = newNode;
  if(aux==NULL)
    l->first = newNode;
  else{
    aux->next = newNode;
  }
  return (Posic)newNode;
}

void remover(Lista list, Posic item){
  head *l = (head*) list;
  posic *aux, *aux2;
  posic *obj = (posic*)item;
  if(l->size==1){
    l->first = NULL;
    l->last = NULL;
  } else{
    if(l->first==obj){
      aux = obj->next;
      aux->prev =  NULL;
      l->first = aux;
    }
    else if(l->last==obj){
      aux = obj->prev;
      aux->next = NULL;
      l->last = aux;
    }
    else{
      aux = obj->prev;
      aux2 = obj->next;
      aux->next =  aux2;
      aux2->prev = aux;
    }
  }
  free(obj);
  l->size--;
  item = NULL;
}

Item get(Lista l, Posic p){
  posic *aux = (posic*) p;
  return aux->content;
}

Posic insertBefore(Lista l, Posic p, Item item){
  head *list = (head*) l;
  posic *ref, *aux, *aux2, *newNode;
  newNode = (posic*) malloc(sizeof(posic));
  ref = (posic*) p;
  if(list->size==1){
    newNode->next = list->first;
    newNode->prev = NULL;
    newNode->content = item;
    aux = list->first;
    aux->prev = newNode;
    list->first = newNode;
  } else{
    if(list->first==ref){
      newNode->prev = NULL;
      newNode->next = ref;
      newNode->content = item;
      ref->prev = newNode;
      list->first = newNode;
    }
    else{
      aux = ref->prev;
      ref->prev = newNode;
      newNode->next = ref;
      newNode->prev = aux;
      newNode->content = item;
      aux->next = newNode;
    }
  }
  list->size++;
  return (Posic)newNode;
}

Posic insertAfter(Lista l, Posic p, Item item){
  head *list = (head*) l;
  posic *ref, *aux, *newNode;
  newNode = (posic*) malloc(sizeof(posic));
  ref = (posic*) p;
  if(list->size==1){
    aux = list->first;
    newNode->next = NULL;
    newNode->content = item;
    newNode->prev = aux;
    aux->next = newNode;
    list->last = newNode;
  } else{
    if(list->last==ref){
      newNode->next = NULL;
      newNode->prev = list->last;
      newNode->content = item;
      list->last = newNode;
      ref->next = newNode;
    }
    else{
      aux = ref->next;
      ref->next = newNode;
      newNode->next = aux;
      newNode->prev = ref;
      newNode->content = item;
      aux->prev = newNode;
    }
  }
  list->size++;
  return (Posic)newNode;
}

Posic getFirst(Lista l){
  head *list = (head*) l;
  return (Posic)list->first;
}

Posic getLast(Lista l){
  head *list = (head*) l;
  return (Posic)list->last;
}

Posic getNext(Lista l, Posic p){
  posic *obj = (posic*) p;
  obj = obj->next;
  return (Posic)obj;
}

Posic getPrevious(Lista l, Posic p){
  posic *obj = (posic*) p;
  obj = obj->prev;
  return (Posic)obj;
}

void liberaLista(Lista l){
  int i;
  head *h = (head*)l;
  posic *p1, *p2;
  if(h->size>1){
    p1 = h->first;
    for(i=h->size;i>0;i--){
      p2 = p1->next;
      free(p1);
      p1 = p2;
    }
  }
}
