#ifndef PROCEDIMENTOS__H
#define PROCEDIMENTOS__H
#include "Circulo.h"
#include "Retangulo.h"
#include "Quadra.h"
#include "Hidrante.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Cidade.h"
#include "Formas.h"
/*PROCEDIMENTOS É O MODULO RESPONSAVEL POR ORGANIZAR OS ARQUIVOS LIDOS E SUAS OPERACOES*/
Cidade processoGeo(char *nomeGeo, char *dirSaida, char *nomeEntradaQry, Formas *formaGeral, Cidade cid);
/*PROCESSO GEO RECEBE OS NOMES DE ENTRADA E OS ARQUIVOS JA ABERTOS.
CRIA E RETORNA UMA CIDADE COM AS INFORMACOES PASSADAS EM ENT.*/
Cidade processoQry(Cidade c, char *nomeBase, char *nomeQry, char *dirBSD);
/*PROCESSO QRY EXCLUI OS OBJETOS DA CIDADE COM BASE NAS INFORMACOES PASSADAS EM ENTQRY.
RETORNA A CIDADE ATUALIZADA.
*/

#endif
