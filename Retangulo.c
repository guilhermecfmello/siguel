#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Retangulo.h"
#include "Lista.h"

	typedef struct _rectangle{
		int id;
		double width;
		double height;
		double x;
		double y;
		char *color;
	}rectangle;

	Rect createRectangle(int id, double width, double height, double xN, double yN,char *color){
		rectangle *newRectangle;
		int sizeColor;
		newRectangle = (rectangle*) malloc(sizeof(rectangle));
		newRectangle->id = id;
		newRectangle->width = width;
		newRectangle->height = height;
		newRectangle->x = xN;
		newRectangle->y = yN;
		sizeColor = strlen(color);
		newRectangle->color = malloc(sizeof(char)*sizeColor+1);
		strcpy(newRectangle->color,color);
		return newRectangle;
	}

	double getRectangleWidth(Rect r){
		rectangle *r1;
		r1 = (rectangle*)r;
		return r1->width;
	}

	double getRectangleHeight(Rect r){
		rectangle *r1;
		r1 = (rectangle*)r;
		return r1->height;
	}
	double getRectangleX(Rect r){
		rectangle *r1;
		r1 = (rectangle*) r;
		return r1->x;
	}
	double getRectangleY(Rect r){
		rectangle *r1;
		r1 = (rectangle*) r;
		return r1->y;
	}
	int getRectangleId(Rect r){
		rectangle *r1;
		r1 = (rectangle*) r;
		return r1->id;
	}
	char *getRectangleColor(Rect r){
		rectangle *r1;
		r1 = (rectangle*) r;
		return r1->color;
	}
	int getRectangleColorLenght(Rect r){
		int size;
		rectangle *r1;
		r1 = (rectangle*) r;
		size = strlen(r1->color);
		return size;
	}

	void writeRectangleSvg(FILE *arq, void *rect){
		double x,y,size1,size2;
		int i, sizeColor;
		char *read;
		x = getRectangleX(rect);
		y = getRectangleY(rect);
		size1 = getRectangleWidth(rect);
		size2 = getRectangleHeight(rect);
		sizeColor = getRectangleColorLenght(rect);
		read = malloc(sizeof(char)*sizeColor+1);
		strcpy(read,getRectangleColor(rect));
		fprintf(arq,"	<rect x=\"%f\" y=\"%f\" width=\"%f\"",x,y,size1);
		fprintf(arq," height=\"%f\" fill=\"%s\"/>\n",size2,read);
		free(read);
	}

	void writeRectSob(FILE *arq, Rect r){
			double x, y, w, h;
			x = getRectangleX(r);
			y = getRectangleY(r);
			w = getRectangleWidth(r);
			h = getRectangleHeight(r);
			if(arq!=NULL){
			fprintf(arq,"	<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\"",x,y,w,h);
			fprintf(arq," fill=\"none\" style=\"stroke:pink;");
			fprintf(arq,"stroke-width:3;stroke-dasharray:");
			fprintf(arq,"5,5\"/>\n");
			x++;
			y = y + 11;
			fprintf(arq,"	<text x=\"%f\" y=\"%f\" fill=\"red\">",x,y);
			fprintf(arq,"sobrepoe</text>\n");
			}
			else{
				printf("\n######DEU RUIM AQUI!");
			}
	}

	void writeRectangleSvgSuf(FILE *arq, void *r, char *color){
		double x,y,w,h,x1,y1;
		x = getRectangleX(r);
		y = getRectangleY(r);
		w = getRectangleWidth(r);
		h = getRectangleHeight(r);
		x1 = x + w;
		y1 = y + h;
		fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",x,y);
		fprintf(arq," r=\"5\" fill=\"%s\"/>\n",color);
		fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",x,y1);
		fprintf(arq," r=\"5\" fill=\"%s\"/>\n",color);
		fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",x1,y);
		fprintf(arq," r=\"5\" fill=\"%s\"/>\n",color);
		fprintf(arq,"	<circle cx=\"%f\" cy=\"%f\"",x1,y1);
		fprintf(arq," r=\"5\" fill=\"%s\"/>\n",color);
	}
	void liberaRect(Rect r){
		rectangle *r1 = (rectangle*) r;
		free(r1->color);
		free(r1);
	}

void getRectInfos(Rect f1,int *id,double *x,double *y, double *w, double *h, char **cor){
	rectangle *r = (rectangle*) f1;
	*x = r->x;
	*y = r->y;
	*w = r->width;
	*h = r->height;
	*id = r->id;
	*cor = r->color;
}

/*
void imprimeRetangulosSob(FILE *arq, Lista list){
	Rect aux, r;
	aux = getFirst(list);
	while(aux!=NULL){
		r = get(list,aux);
		writeRectSob(arq,r);
		aux = getNext(list, aux);
	}
}*/
