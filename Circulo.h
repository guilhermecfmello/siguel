#ifndef CIRCULO__H
#define CIRCULO__H
typedef void* Circle;

	Circle createCircle(int i, double r, double xN, double yN, char *c);
	/*createCircle cria uma elemento circulo com a id i, raio r,
	coordenadas xN e yN, e cor c.
	*/
	void getCircleInfos(Circle circleVerify, int *i,double *r, double *x, double *y, char **cor);
	/*Recebe um Circulo e as seguintes referencias: id, raio, x, y, cor;
	Retorna nos tipos de dados passados como referencia as informações do Circulo
	*/
	double getCircleX(Circle circleVerify);
	/*recebe um ponteiro void para uma struct de Circle e retorna a
	coordenada X da forma.
	*/
	double getCircleY(Circle circleVerify);
	/*recebe um ponteiro void para uma struct de Circle e retorna a
	coordenada Y da forma.
	*/
	double getCircleRaio(Circle circleVerify);
	/*recebe um ponteiro void para uma struct de Circle e
	retorna o raio da forma.
	*/
	int getCircleId(Circle circleVerify);
	/*recebe um ponteiro void para uma struct de Circle e retorna a
	ID da forma.
	*/
	int getCircleColorLenght(Circle circleVerify);
	/*recebe um círculo retorna o
	tamanho da string que guarda a cor do circulo
	*/
	char *getCircleColor(Circle circleVerify);
	/*recebe um ponteiro void para uma struct de Circle e retorna um
	ponteiro para a string que guarda a cor da forma.
	*/
	void writeCircleSvg(FILE *arq, void *circle);
	/*recebe o ponteiro para um arquivo já aberto e um ponteiro para um circulo,
	escreve no arquivo "arq" as tags para formar um circulo svg.
	*/
	void writeCircleSvgSuf(FILE *arq, void *c, char *color);
	/*Recebe um ponteiro para um arquivo de saída já aberto, um ponteiro para um
	circulo e a cor dele.
	Escreve no arquivo um circulo de raio 5 da cor color no centro
	da figura C.
	*/
	void liberaCircle(Circle c);
	/*Recebe um circulo C e da free no ponteiro da sua cor e free no
	proprio circulo
	*/
#endif
