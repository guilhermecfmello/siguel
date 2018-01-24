#ifndef OPERACOES__H
#define OPERACOES__H
#include "Quadra.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Lista.h"
#include "Quadtree.h"
#include "ConvexHull.h"

typedef void* Forma;

int parametroId(int argc, char *argv[]);

int parametroAcc(int argc, char *argv[]);

char *pegaParametro(int argc,  char *argv[], char *parametro);

int verPointRect(Forma f, double x2, double y2);
/*Verifica se as coordenadas "x2" e "y2" são internas da Forma f, que é um void
pointer de retangulo. Retorna 1 se for interna e 0
se não.
*/
int verRectRect(Forma r1, Forma r2);
/*Recebe dois void pointers para r1 e r2, que são dois retangulos e verifica se
um sobrepõe o outro.
*/
double maiorDouble(double a, double b);
/*Recebe o double "a" e double "b", retorna o maior deles
*/
double menorDouble(double a, double b);
/*Recebe o double "a" e double "b", retorna o menor deles
*/
double distanceBetweenPoints(double x1, double y1, double x2, double y2);
/*Recebe 2 pontos de um plano cartesiano, (x1,y1) e (x2,y2).
Retorna a distancia entra os pontos
*/
int verCircCirc(Forma c1, Forma c2);
/*Recebe dois ponteiros void para dois circulos, retorna 1 se eles
se sobrepõem e 0 se não
*/
double difXRaio(Forma c1, Forma c2, int op);
/*Recebe dois ponteiros void para circulo e um inteiro
"op".
  Caso OP seja 1: Retorna o maior (X+raio) entre os dois circulos.
  Caso OP seja 0: Retorna o menor (X-raio) entre os dois circulos.
*/
double difYRaio(Forma c1, Forma c2, int op);
/*Recebe dois ponteiros void para ciruclo e um inteiro
"op".
Caso OP seja 0: Retorna o maior (y+raio) entre os circulos
Caso OP seja 1: Retorna o menor (y-raio) entre os circulos
*/
double difXW(Forma r1,Forma r2);
/*Recebe dois ponteiros void para retangulos
Retorna a maior coordenada x somada com sua largura entre
eles
*/
double maiorYplusH(Forma r1, Forma r2);
/*Recebe dois ponteiros void para retangulo,
Retorna a maior coordenada y somada com sua respectiva
altura.
*/
int verPointCirc(Forma c, double x2, double y2);
/*Recebe um ponteiro void para um circulo e dois doubles,
que representam uma coordenada num plano cartesiano.
Verifica se o ponto correspondente à coordenada (x2,y2)
é interno ao circulo, caso seja verdade, retorna 1.
Retorna 0 caso não seja.
*/
int verCircRect(Forma c, Forma r);
/*Recebe 2 ponteiros void, o primeiro para um circulo e
o segundo para um retangulo, caso se sobreponham, retorna 1.
Retorna 0 caso contrário.
*/
double getMaiorYCircRect(Forma c, Forma r);
/*Recebe dois ponteiros void, o primeiro para um circulo
e o segundo para um retangulo.
Retorna o ponto "Y" mais distante do eixo "X" no plano cartesiano
entre eles.
*/
double getMaiorXCircRect(Forma c, Forma r);
/*Recebe dois ponteiros void, o primeiro para um circulo
e o segundo para um retangulo.
Retorna o ponto "X" mais distante do eixo "Y" no plano cartesiano
entre eles.
*/
int verPontoInterno(Forma x,char tipo,double x2,double y2);
/*Recebe o ponteiro void, que pode ser um circulo ou retangulo.
O char "tipo" terá 'r' se x for retangulo e 'c' se for
circulo. Então verifica se a coordenada (x2,y2) é interna
à forma. Retorna 1 se for verdadeiro e 0 se falso.
*/
int verPointCircInt(Forma c, double x2, double y2);
/*recebe um ponteiro void para um circulo e dois doubles
que representam uma coordenada no plano cartesiano.
Retorna 1 se a coordenada for interna ao circulo e 0
caso contrario.
*/
int verPointRectInt(Forma f, double x2, double y2);
/*recebe um ponteiro void para um retangulo e dois doubles
que representam uma coordenada no plano cartesiano.
Retorna 1 se a coordenada for intera ao circulo e 0
caso contrario.
*/
double getCentroX(Forma f, char c);
/*Recebe um ponteiro void para uma forma que pode ser circulo
ou retanglo, "char c" especifica o tipo ('c' e 'r' respectivamente)
Retorna o ponto x da mediana da forma.
*/
double getCentroY(Forma f, char c);
/*Recebe um ponteiro void para uma forma que pode ser circulo
ou retanglo, "char c" especifica o tipo ('c' e 'r' respectivamente)
Retorna o ponto y da mediana da forma.
*/
double verCentroMassa(Forma a, Forma b,char a1, char b1);
/*Recebe dois ponteiros void para duas formas,
retorna a distancia entre os centro de massa das duas.
*/


double getMenorXCircRect(Forma c, Forma r);

double getMenorYCircRect(Forma c, Forma r);



int verQuadraRet(Quadra q, Rect r);
/*Recebe uma quadra e um retangulo
Se a Quadra estiver inteiramente contida no retangulo, retorna 1;
Caso contrario, retorna 0;
*/
int verQuadraCirc(Quadra q, Circle c);
/*Recebe uma quadra e um circulo
Se a quadra estiver inteiramente contida no ciculo, retorna 1
Caso contrario, retorna 0;
*/
void hidListToVector();
/*Recebe uma lista de hidrantes, transfere os dados para um vetor.
*/
Tree listToQuadtree(Lista l, getX gx, getY gy);
/*Recebe uma lista de elementos da cidade, e duas funcoes.
Retorna uma arvore balanceada atraves do algoritmo convexhull.
*/

#endif
