#ifndef QUADRA__H
#define QUADRA__H

typedef void* Quadra;

Quadra createQuadra(double x, double y, double w, double h, char *end);
/*x, y, w e h devem ser valores reais maiores que zero. End deve ser uma string.
Cria e retorna uma quadra com as informações passadas.
*/
double getQuadraX(Quadra qua);
/*Recebe uma quadra.
Retorna o ponto X da quadra.
*/
double getQuadraY(Quadra qua);
/*Recebe uma quadra.
Retorna o ponto y da quadra.
*/
double getQuadraW(Quadra qua);
/*Recebe uma quadra.
Retorna a largura da quadra.
*/
double getQuadraH(Quadra qua);
/*Recebe uma quadra.
Retorna a altura da quadra.
*/
char *getQuadraCep(Quadra qua);
/*Recebe uma quadra.
Retorna o cep da quadra.
*/
void getQuadraInfos(Quadra qua, double *x, double *y, double *w, double *h, char **end);
/*Recebe uma quadra, 4 variaveis tipo double e uma ponteiro char como referencia.
Retorna em forma de referencia nas variaveis passadas as informações da quadra na seguinte ordem:
x, y, largura, altura, cep
*/

void apagaQuadraCep(Quadra qua);
/*Recebe uma quadra
Apaga o cep da Quadra
*/

#endif
