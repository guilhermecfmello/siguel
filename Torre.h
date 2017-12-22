#ifndef TORRE__H
#define TORRE__H

typedef void* Torre;

Torre createTorre(double x, double y, char *id);
/*Recebe coordenadas x e y do plano cartesiano, que devem ser maiores que zero, e uma string id,
que identifica a torre, portanto, deve ser unica entre as existentes.
Retorna a nova torre criada com as informacoes passadas.
*/
double getTorreX(Torre tor);
/*Recebe uma torre.
Retorna a coordenada x dela.
*/
double getTorreY(Torre tor);
/*Recebe uma torre.
Retorna a coordenada y dela.
*/
char *getTorreId(Torre tor);
/*Recebe uma torre.
Retorna a string de identificacao dela.
*/
void getTorreInfos(Torre tor, double *x, double *y, char **id);
/*Recebe um torre, e tres variaveis como referencia.
Altera as variaveis como referencia, colocando os calores referentes a torre passada, na seguinte ordem: x, y, id.
*/
void apagaTorreID(Torre tor);
/*Recebe uma torre
Apaga o seu ID.
*/

void setTorreRaio(Torre tor, double r);
/*Recebe uma torre e um double que representa o raio de cobertura da torre.
Seta a torre com o raio passado;
*/
#endif
