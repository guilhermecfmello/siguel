#ifndef RETANGULO__H
#define RETANGULO__H

typedef void* Rect;

	Rect createRectangle(int id, double width, double height, double xN, double yN,char *color);
	double getRectangleWidth(Rect r);
	double getRectangleHeight(Rect r);
	double getRectangleX(Rect r);
	double getRectangleY(Rect r);
	int getRectangleId(Rect r);
	char *getRectangleColor(Rect r);
	int getRectangleColorLenght(Rect r);
	void writeRectangleSvg(FILE *arq, Rect rect);
	void writeRectSob(FILE *arq, Rect r);
	void writeRectangleSvgSuf(FILE *arq,Rect r, char *color);
	void liberaRect(void* r);
	void getRectInfos(Rect f1,int *id, double *x,double *y, double *w, double *h, char **cor);
	

#endif
