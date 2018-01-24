#ifndef DICIONARIO__H
#define DICIONARIO__H

#include "Hash.h"
#include "Pessoa.h"
#include "Torre.h"
#include "Quadra.h"
#include "Estabelecimento.h"
#include "Telefone.h"

/*O TAD DICIONARIO ARMAZENA TABELAS HASH DE CONSULTA SOBRE ALGUNS ELEMENTOS DA CIDADE.
OS SEGUINTES ITENS PODEM SER INSERIDOS E BUSCADOS:
-PESSOAS
-RADIOBASES
-ESTABELECIMENTOS
-DESCRICAO DOS ESTABELECIMENTOS
-QUADRAS*/

typedef void* Dicionario;

Dicionario dicionario_create();

Hash getHash(Dicionario di, char *type);
/*Consulta do dicionario*/

void dicio_insere_pessoaCpf(Dicionario di, Pessoa p);
/*Insere a pessoa P na tabela hash usando seu cpf como key.*/

void dicio_insere_pessoaNumCel(Dicionario di, Pessoa p);
/*A pessoa deve ter um telefone.
Insere a pessoa p na hash, usando seu telefone como key*/

void dicio_insere_radiobaseNumCel(Dicionario di, Torre tor, char *num);
/*Dado um numero de celular, adiciona na Hash a radiobase usando uma copia deste
numero como chave.*/

void dicio_insere_estType(Dicionario di, Estab est, char *key);
/*Insere o estabelecimento est em uma tabela hash, utilizando uma copia do tipo
(codt) como chave*/

void dicio_insere_Desctype(Dicionario di, char *desc, char *type);
/*Insere uma string de descricao de um tipo de estabelecimento na tabela hash.
O tipo eh usado como chave e ambos sao utilizados como copia.*/

void dicio_insere_quadraCep(Dicionario di, Quadra qua);
/*Insere a quadra em uma tabela hash, usando como chave seu cep*/

Pessoa dicio_searchPessoa_cpf(Dicionario di, char *key);
/*Busca na Hash a pessoa, uhtilizando o cpf como chave, retorna NULL caso nao encontre.*/

Pessoa dicio_searchPessoa_numcel(Dicionario di, char *key);
/*Busca na hash a pessoa, utilizando o numero de celular como chave. Retorna
NULL caso nao encontre*/

Torre dicio_searchRadio_numcel(Dicionario di, char *key);
/*Busca na hash a radiobase, utilizando o numero do celular como chave Retorna
NULL caso nao encontre*/
char *dicio_searchDesc_type(Dicionario di, char *key);
/*Busca na hash de descricoes de estabelecimento, utilizando o tipo (codt) do
estabelecimento como chave. Retorna NULL caso nao encontre*/
Estab dicio_search_Estab_type(Dicionario di, char *key);
/*Busca na hash de estabelecimento utilizando o tipo (codt) como chave. Retorna
NULL caso nao encontre*/
Quadra dicio_search_Quadra_cep(Dicionario di, char *key);
/*Busca na hash de quadras, utilizando o cep como chave. Retorna NULL caso nao
encontre*/

/*==========Implementar caso de tempo==========*/

void dicio_libera(Dicionario di, char *hash);
/*Libera a memoria utilizada pela hash*/

#endif
