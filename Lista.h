#ifndef LISTA_H
#define LISTA_H

typedef void* Lista;
typedef void* Posic;
typedef void* Item;

Lista createList();
int length(Lista list);
void remover(Lista list, Posic item);
Posic insert(Lista list, Lista item);
Posic insertBefore(Lista l, Posic p, Item item);
Posic insertAfter(Lista l, Posic p, Item item);
Posic getFirst(Lista l);
Posic getLast(Lista l);
Posic getNext(Lista l, Posic p);
Posic getPrevious(Lista l, Posic p);
Item get(Lista l, Posic p);
void liberaLista(Lista l);

#endif
