#ifndef HIDRANTE__H
#define HIDRANTE__H

typedef void* Hidrante;

Hidrante createHidrante(double x, double y, char *id);
/*Recebe as posicoes X e Y do hidrante no plano cartesiano, que devem ser maiores que zero.
Também recebe uma string ID que identifica o hidrante, deve ser unica entre todos os hidrantes existentes.
Cria e retorna o hidrante com as informações passadas.
*/
double getHidranteX(Hidrante hid);
/*Recebe um hidrante.
Retorna a posicao x do hidrante.
*/
double getHidranteY(Hidrante hid);
/*Recebe um hidrante.
Retorna a posicao y do hidrante.
*/
char *getHidranteId(Hidrante hid);
/*Recebe um hidrante.
Retorna a string de identificacao do hidrante.
*/
void getHidranteInfos(Hidrante hid, double *x, double *y, char **id);
/*Recebe um hidrante, e mais tres referencias de variáveis, x y e Id.
O procedimento atualiza por referencia as variaveis passadas por parametro.
*/

void apagaHidranteID(Hidrante hid);
/*Recebe um hidrante
Apaga o id do hidrante
*/

void setHidranteVazao(Hidrante hid, double vazao);
/*RECEBE UM HIDRANTE E UM DOUBLE QUE REPRESENTA A SUA VAZAO EM LITROS/SEGUNDO
CASO O HIDRANTE SEJA NULO, NAO FAZ NADA.
*/

#endif
