#ifndef FORMAS__H
#define FORMAS__H
#include "Circulo.h"
#include "Retangulo.h"
#include "Lista.h"
#include "Operacoes.h"
/*ALTERADOS:
#procuraFigura

*/
typedef void* Formas;

Formas createFormas();
/*
*/

Circle insereCirculo(Formas f, Circle circul);
/*
*/
Rect insereRetangulo(Formas f, Rect retan);
/*
*/
Rect insereSob(Formas f, Rect retan);
/*
*/
Circle getCirculos(Formas f);
/*
*/
Rect getRetangulos(Formas f);
/*
*/
Rect getSobreposicoes(Formas f);
/*
*/

Forma procuraCirc(Forma list, int id);
/*Recebe uma lista de circulos e um id, procura
nessa lista um circulo com essa id.
Retorna o ciculo se econtrar, caso contrario, retorna NULL.
*/
Forma procuraRect(Forma list, int id);

int procuraFigura(Forma *f1, char *typeF1, Formas f, int id);

void imprimeRetangulosSuf(FILE *arq, Forma list, char *color);

void imprimeCirculosSuf(FILE *arq, Forma list, char *color);

void removeFormas(Formas f);
/*Remove todas a formas, libera a memoria
*/

void moduloO(double *x, double *y, double *larg, double *alt, int *cond, char typeF1, char typeF2, Forma f1, Forma f2);
/*A IMPLEMENTAR*/

void imprimeRetangulosSob(FILE *arq, Formas f);

void imprimeRetangulos(FILE *arq, Formas f);

void imprimeCirculos(FILE *arq, Formas f);

#endif
