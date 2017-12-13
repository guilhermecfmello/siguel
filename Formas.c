#include <stdio.h>
#include <stdlib.h>
#include "Formas.h"

typedef struct _formas{
  Lista circulos;
  Lista retangulos;
  Lista sobreposicoes;

}formas;

Formas createFormas(){
  formas *f;
  f = (formas*)malloc(sizeof(formas));
  f->circulos = createList();
  f->retangulos = createList();
  f->sobreposicoes = createList();
  return f;
}

Circle insereCirculo(Formas f, Circle circul){
  formas *form = (formas*) f;
  insert(form->circulos, circul);
  return circul;
}

Rect insereRetangulo(Formas f, Rect retan){
  formas *form = (formas*) f;
  insert(form->retangulos, retan);
  return retan;
}

Rect insereSob(Formas f, Rect retan){
  formas *form = (formas*) f;
  insert(form->sobreposicoes, retan);
  return retan;
}

Circle getCirculos(Formas f){
  formas *form = (formas*) f;
  return form->circulos;
}

Rect getRetangulos(Formas f){
  formas *form = (formas*) f;
  return form->retangulos;
}

Rect getSobreposicoes(Formas f){
  formas *form = (formas*) f;
  return form->sobreposicoes;
}

int procuraFigura(Forma *f1, char *typeF1, Formas f, int id){
  formas *form = (formas*) f;
  *f1 = procuraCirc(form->circulos,id);
  if(*f1!=NULL){
    *typeF1 = 'c';
    return 1;
  }
  else{
    *f1 = procuraRect(form->retangulos,id);
    if(f1!=NULL){
     *typeF1 = 'r';
     return 1;
    }
    else return 0;
  }
}

Forma procuraCirc(Lista list, int id){
  int i;
  Forma aux, fig, achou;
  fig = NULL;
  achou = NULL;
  aux = getFirst(list);
  while(aux!=NULL){
    fig = get(list,aux);
    if(getCircleId(fig)==id){
      achou = fig;
      break;
    }
    aux = getNext(list,aux);
  }
  return achou;
}

Forma procuraRect(Lista list, int id){
  Forma aux, fig, achou;
  fig = NULL;
  achou = NULL;
  aux = getFirst(list);
  while(aux!=NULL){
    fig = get(list,aux);
    if(getRectangleId(fig)==id){
      achou = fig;
      break;
    }
    aux = getNext(list,aux);
  }
  return achou;
}

void imprimeRetangulosSuf(FILE *arq,Formas f, char *color){
  formas *form = (formas*) f;
	Rect aux, r;
	aux = getFirst(form->retangulos);
	while(aux!=NULL){
		r = get(form->retangulos,aux);
		writeRectangleSvgSuf(arq,r,color);
		aux = getNext(form->retangulos,aux);
	}
}

void imprimeCirculosSuf(FILE *arq,Formas f, char *color){
  formas *form = (formas*) f;
	Circle aux, c;
	aux = getFirst(form->circulos);
	while(aux!=NULL){
		c = get(form->circulos,aux);
		writeCircleSvgSuf(arq,c,color);
		aux = getNext(form->circulos,aux);
	}
}

void liberaListaCirculos(Lista lista){
  Circle c, aux, aux2;
  aux = getFirst(lista);
  while(aux!=NULL){
    c = get(lista,aux);
    liberaCircle(c);
    aux2 = aux;
    aux = getNext(lista,aux);
    remover(lista,aux2);
  }
}

void liberaListaRetangulos(Lista lista){
  Rect r, aux, aux2;
  aux = getFirst(lista);
  while(aux!=NULL){
    r = get(lista,aux);
    liberaRect(r);
    aux2 = aux;
    aux = getNext(lista,aux);
    remover(lista,aux2);
  }
}

void removeFormas(Formas f){
  formas *form = (formas*) f;
  liberaListaCirculos(form->circulos);
  liberaListaRetangulos(form->retangulos);
  liberaListaRetangulos(form->sobreposicoes);
}

void moduloO(double *x, double *y, double *larg, double *alt, int *cond, char typeF1, char typeF2, Forma f1, Forma f2){
  if(typeF1=='c'&&typeF2=='c'){
    *x = difXRaio(f1,f2,0);
    *y = difYRaio(f1,f2,0);
    *larg = difXRaio(f1,f2,1)-*x;
    *alt = difYRaio(f1,f2,1) -*y;
    *cond = verCircCirc(f1,f2);
  } else if(typeF1=='r'&&typeF2=='r'){
    *x = menorDouble(getRectangleX(f1),getRectangleX(f2));
    *y = menorDouble(getRectangleY(f1),getRectangleY(f2));
    *larg = difXW(f1,f2) - *x;
    *alt = maiorYplusH(f1,f2) - *y;
    *cond = verRectRect(f1,f2);
  } else if(typeF1 == 'c'){
    *x = getMenorXCircRect(f1,f2);
    *y = getMenorYCircRect(f1,f2);
    *larg = getMaiorXCircRect(f1,f2) - *x;
    *alt = getMaiorYCircRect(f1,f2) - *y;
    *cond = verCircRect(f1,f2);
  } else if(typeF1 == 'r'){
    *x = getMenorXCircRect(f2,f1);
    *y = getMenorYCircRect(f2,f1);
    *larg = getMaiorXCircRect(f2,f1) - *x;
    *alt = getMaiorYCircRect(f2,f1) - *y;
    *cond = verCircRect(f2,f1);
  }
}


void imprimeRetangulos(FILE *arq, Formas f){
  formas *form = (formas*) f;
	Rect aux, r;
	aux = getFirst(form->retangulos);
	while(aux!=NULL){
		r = get(form->retangulos,aux);
		writeRectangleSvg(arq,r);
		aux = getNext(form->retangulos,aux);
	}
}

void imprimeRetangulosSob(FILE *arq, Formas f){
  double x, y, w, h;
  formas *form = (formas*) f;
	Rect aux, r;
	aux = getFirst(form->sobreposicoes);
	while(aux!=NULL){
		r = get(form->sobreposicoes,aux);
    x = getRectangleX(r);
    y = getRectangleY(r);
    w = getRectangleWidth(r);
    h = getRectangleHeight(r);
    fprintf(arq,"<rect x=\"%f\" y=\"%f\" width=\"%f\" height =\"%f\"",x,y,w,h);
    fprintf(arq," fill=\"none\" style=\"stroke:pink;");
    fprintf(arq,"stroke-width:3;stroke-dasharray:");
    fprintf(arq,"5,5\"/>\n");
    x++;
    y = y + 11;
    fprintf(arq,"<text x=\"%f\" y=\"%f\" fill=\"red\">",x,y);
    fprintf(arq,"sobrepoe</text>\n");
		aux = getNext(form->sobreposicoes,aux);
	}
}

void imprimeCirculos(FILE *arq, Formas f){
  formas *form = (formas*) f;
	Circle aux, c;
	aux = getFirst(form->circulos);
	while(aux!=NULL){
		c = get(form->circulos,aux);
		writeCircleSvg(arq,c);
		aux = getNext(form->circulos,aux);
	}
}
