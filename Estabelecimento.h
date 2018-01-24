#ifndef ESTABELECIMENTO__H
#define ESTABELECIMENTO__H

typedef void* Estab;

Estab estab_create(char *cnpj, char *nome, char *codt,char *cep, char face, int num);

char *estab_get_cnpj(Estab est);

char *estab_get_nome(Estab est);

char *estab_get_codt(Estab est);

char *estab_get_cep(Estab est);

char estab_get_face(Estab est);

int estab_get_num(Estab est);

#endif
