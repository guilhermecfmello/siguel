#ifndef TELEFONE__H
#define TELEFONE__H

typedef void* Telefone;


Telefone telefone_create(char *num, char *radiobase);

char *telefone_get_num(Telefone tel);

char *telefone_get_radiobase(Telefone tel);

void telefone_set_num(Telefone tel, char *num);

void telefone_set_radiobase(Telefone tel, char *radiobase);

#endif
