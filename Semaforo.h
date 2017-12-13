#ifndef SEMAFORO__H
#define SEMAFORO__H

typedef void* Semaforo;

Semaforo createSemaforo(double x, double y, char *id);
/*Recebe um X e Y do plano cartesiano, que devem ser maiores que zero.
Também recebe uma string ID que identifica o semaforo, portanto deve ser unica entre os existentes.
Retorna o semaforo criado.
*/
double getSemaforoX(Semaforo sem);
/*Recebe um semaforo.
Retorna a posicao X do semaforo no plano cartesiano.
*/
double getSemaforoY(Semaforo sem);
/*Recebe um semaforo.
Retorna a posicao Y do semaforo no plano cartesiano.
*/
char *getSemaforoId(Semaforo sem);
/*Recebe um semaforo.
Retorna uma string com o id do semaforo passado.
*/
void getSemaforoInfos(Semaforo sem, double *x, double *y, char **id);
/*Recebe um semaforo, e referencia para 3 variaveis, duas double e uma string.
Altera por referencia as variaveis com as informacoes do semaforo, na seguinte ordem: x, y, e id.
*/

void apagaSemaforoID(Semaforo sem);
/*Recebe um semaforo
Apaga o id do semaforo
*/
#endif
