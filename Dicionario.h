#ifndef DICIONARIO__H
#define DICIONARIO__H

#include "Hash.h"
#include "Pessoa.h"
#include "Torre.h"
#include "Quadra.h"
#include "Estabelecimento.h"
#include "Telefone.h"
#include "Lista.h"

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
/*Insere a pessoa P na tabela hash usando uma copia do seu cpf como key.*/

void dicio_insere_pessoaNumCel(Dicionario di, Pessoa p);
/*A pessoa deve ter um telefone.
Insere a pessoa p na hash, usando seu telefone como key*/

void dicio_insere_radiobaseNumCel(Dicionario di, char *torre, char *num);
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

char *dicio_searchRadio_numcel(Dicionario di, char *key);
/*Busca na hash a radiobase, utilizando o numero do celular como chave Retorna
NULL caso nao encontre*/

void dicio_remove_radio_numcel(Dicionario di, char *key);

char *dicio_searchDesc_type(Dicionario di, char *key);
/*Busca na hash de descricoes de estabelecimento, utilizando o tipo (codt) do
estabelecimento como chave. Retorna NULL caso nao encontre*/
Estab dicio_search_Estab_type(Dicionario di, char *key);
/*Busca na hash de estabelecimento utilizando o tipo (codt) como chave. Retorna
NULL caso nao encontre*/
Quadra dicio_search_Quadra_cep(Dicionario di, char *key);
/*Busca na hash de quadras, utilizando o cep como chave. Retorna NULL caso nao
encontre*/

void dicio_insere_cpf_sercomtuel(Dicionario di, char *cpf, char *num);
/*Define o cpf passado como cliente da sercomtuel*/
void dicio_insere_cpf_uelmobile(Dicionario di, char *cpf, char *num);
/*Define o cpf passado como cliente da uelMobile*/
char *dicio_search_cpf_sercomtuel(Dicionario di, char *num);
/*Busca na hash da sercomtuel o cpf do cliente de numero num.*/
char *dicio_search_cpf_uelmobile(Dicionario di, char *num);
/*Busca na hash da uelmobile o cpf do cliente de numero num.*/
void dicio_insere_torre_sercomtuel(Dicionario di, Torre tor);
/*Insere a torre tor na hash de torres da sercomtuel, usando uma copia do seu ID como key*/
void dicio_insere_torre_uelmobile(Dicionario di, Torre tor);
/*Insere a torre tor na hash de torres da uelmobile, usando uma copia do seu ID como key*/

Torre dicio_search_torre_sercomtuel(Dicionario di, char *id);
/*Busca na hash de torres da sercomtuel usando o id passado como chave*/
Torre dicio_search_torre_uelmobile(Dicionario di, char *id);
/*Busca na hash de torres da uelmobile usando o id passado como chave*/

Lista dicio_get_all_torres_sercomtuel(Dicionario di);

Lista dicio_get_all_torres_uelmobile(Dicionario di);

/*==========Implementar se der tempo==========*/

void dicio_libera(Dicionario di, char *hash);
/*Libera a memoria utilizada pela hash*/

#endif
