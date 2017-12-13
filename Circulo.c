#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circulo.h"
#include "Lista.h"

typedef struct _circle{
	int id;
	double raio;
	double x;
	double y;
	char *color;
}circle;

Circle createCircle(int i, double r, double xN, double yN, char *c){
	circle *newCircle = (circle*)malloc(sizeof(circle));
	int sizeColor;
	newCircle->id = i;
	newCircle->raio = r;
	newCircle->x = xN;
	newCircle->y= yN;
	sizeColor=strlen(c);
	newCircle->color = malloc(sizeof(char)*sizeColor+1);
	strcpy(newCircle->color,c);
	return newCircle;
}

double getCircleX(Circle circleVerify){
	circle *c;
	c = (circle*) circleVerify;
	return c->x;
}

double getCircleY(Circle circleVerify){
	circle *c;
	c = (circle*) circleVerify;
	return c->y;
}

double getCircleRaio(Circle circleVerify){
	circle *c;
	c = (circle*) circleVerify;
	return c->raio;
}

int getCircleId(Circle circleVerify){
	circle *c;
	c = (circle*)circleVerify;
	return c->id;
}

int getCircleColorLenght(Circle circleVerify){
	int size;
	circle *c;
	c = (circle*) circleVerify;
	size = strlen(c->color);
	return size;
}

char *getCircleColor(Circle circleVerify){
	circle *c = (circle*) circleVerify;
	return c->color;
}

void writeCircleSvg(FILE *arq, Circle circleVerify){
	circle *c = (circle*) circleVerify;
	fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",c->x,c->y);
	fprintf(arq," r=\"%f\" fill=\"%s\"/>\n",c->raio,c->color);
}

void writeCircleSvgSuf(FILE *arq, void *c, char *color){
	circle *c1 = (circle*) c;
	fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",c1->x,c1->y);
	fprintf(arq," r=\"5\" fill=\"%s\"/>\n", color);
}

void liberaCircle(void *c){
	circle *c1 = (circle*)c;
	free(c1->color);
	free(c1);
}

void getCircleInfos(Circle circleVerify, int *i,double *r, double *x, double *y, char **cor){
	circle *c = (circle*) circleVerify;
	*i = c->id;
	*r = c->raio;
	*x = c->x;
	*y = c->y;
	*cor = c->color;
}
