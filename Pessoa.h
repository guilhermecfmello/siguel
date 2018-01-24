#ifndef PESSOA__H
#define PESSOA__H

#include "Telefone.h"

typedef void* Pessoa;

Pessoa pessoa_create(char *cpf, char *nome, char *sobrenome,char sexo, char *nasc);

char *pessoa_get_cpf(Pessoa pes);

char *pessoa_get_nome(Pessoa pes);

char *pessoa_get_sobrenome(Pessoa pes);

char pessoa_get_sexo(Pessoa pes);

char *pessoa_get_nasc(Pessoa pes);

/**/
char *pessoa_get_cep(Pessoa pes);

char *pessoa_get_face(Pessoa pes);

char *pessoa_get_num(Pessoa pes);

char *pessoa_get_comp(Pessoa pes);

void pessoa_set_cep(Pessoa pes, char *cep);

void pessoa_set_face(Pessoa pes, char *face);

void pessoa_set_num(Pessoa pes, char *num);

void pessoa_set_comp(Pessoa pes, char *comp);

void pessoa_set_tel(Pessoa pes, Telefone tel);

Telefone pessoa_get_tel(Pessoa pes);


#endif
