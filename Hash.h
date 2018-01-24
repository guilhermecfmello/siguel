#ifndef HASH__H
#define HASH__H

typedef void *Hash;
typedef void* RegH;
typedef void* PosicH;

Hash createHash(int size);

RegH hash_insert(Hash ha, PosicH content, char* key);
/*Insere um elemento na tabela hash*/

Hash hash_remove(Hash ha, char* key);
/*Remove um elemento da Hash*/

int hash_code(Hash ha, char* key);
/*Gera o indice do elemento*/

RegH hash_search(Hash ha, char* key);

void imprimeTeste(Hash ha);

char *getKey(Hash ha, RegH re);

char *getContent(Hash ha, RegH re);

#endif
