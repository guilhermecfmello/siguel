#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Operacoes.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Lista.h"

int parametroId(int argc, char *argv[]){
  int i, j;
  for(i=1;i<argc;i++){
    if(strcmp(argv[i],"-id")==0)
      return 1;
  }
  return 0;
}

int parametroAcc(int argc, char *argv[]){
  int i, j;
  for(i=1;i<argc;i++){
    if(strcmp(argv[i],"-acc")==0){
      return 1;
    }
  }
  return 0;
}

char *pegaParametro(int argc,  char *argv[], char *parametro){
  int i, j;
  char *aux;
  aux = NULL;
  for(i=1;i<argc;i++){
    if(strcmp(argv[i],parametro)==0){
      j = strlen(argv[i+1]);
      aux = (char*)malloc(sizeof(char)*(j+1));
      strcpy(aux,argv[i+1]);
    }
  }
  return aux;
}

int verRectRect(Forma r1, Forma r2){
  double x2,y2,w2,h2, aux1, aux2;
  x2 = getRectangleX(r2);
  y2 = getRectangleY(r2);
  w2 = getRectangleWidth(r2);
  h2 = getRectangleHeight(r2);
  aux1 = y2+h2;
  aux2 = x2+w2;
  if(verPointRect(r1,x2,y2))return 1;
  else if(verPointRect(r1,x2,aux1))return 1;
  else if(verPointRect(r1,aux2,y2))return 1;
  else if(verPointRect(r1,aux2,aux1)) return 1;
  else return 0;
}

int verCircCirc(Forma c1, Forma c2){
  double r1,r2,d;
  double x1,y1,x2,y2;
  x1 = getCircleX(c1);
  y1 = getCircleY(c1);
  x2 = getCircleX(c2);
  y2 = getCircleY(c2);
  r1 = getCircleRaio(c1);
  r2 = getCircleRaio(c2);
  d = distanceBetweenPoints(x1,y1,x2,y2);
  if(d<=(r1+r2))return 1;
  else return 0;
}

int verPointRect(Forma f, double x2, double y2){
  double x1, y1, h1, w1;
  x1 = getRectangleX(f);
  y1 = getRectangleY(f);
  h1 = getRectangleHeight(f);
  w1 = getRectangleWidth(f);
  if((x2>=x1)&&(x2<=(x1+w1))&&(y2>=y1)&&(y2<=(y1+h1))){
    return 1;
  }
  else return 0;
}

int verPointCirc(Forma c, double x2, double y2){
  double x1,y1,r1, d;
  x1 = getCircleX(c);
  y1 = getCircleY(c);
  r1 = getCircleRaio(c);
  d = distanceBetweenPoints(x1,y1,x2,y2);
  if(d<=r1)return 1;
  else return 0;
}
double distanceBetweenPoints(double x1, double y1, double x2, double y2){
  double result, soma1, soma2;
  soma2 = x1-x2;
  soma1 = pow(soma2,2);
  result = y1-y2;
  soma2 = pow(result,2);
  soma2 = soma1+soma2;
  result = sqrt(soma2);
  return result;
}

double maiorDouble(double a, double b){
  if(a>b) return a;
  else return b;
}
double menorDouble(double a, double b){
  if(a<b) return a;
  else return b;
}

double difXRaio(Forma c1, Forma c2, int op){
  double x1,r1,x2,r2, m;
  x1 = getCircleX(c1);
  r1 = getCircleRaio(c1);
  x2 = getCircleX(c2);
  r2 = getCircleRaio(c2);
  if(op==0){
    if((x1-r1)<=(x2-r2))m = x1-r1;
    else m = x2-r2;
  }
  else{
    if((x1+r1)>=(x2+r2)) m = x1+r1;
    else m = x2+r2;
  }
  return m;
}

double difYRaio(Forma c1, Forma c2, int op){
  double y1,r1,y2,r2, m;
  y1 = getCircleY(c1);
  r1 = getCircleRaio(c1);
  y2 = getCircleY(c2);
  r2 = getCircleRaio(c2);
  if(op==0){
    if((y1-r1)<=(y2-r2)) m = y1-r1;
    else m = y2-r2;
  }
  else{
    if((y1+r1)>=(y2+r2)) m = y1+r1;
    else m = y2 + r2;
  }
  return m;
}

double difXW(Forma r1,Forma r2){
  double x1,w1,x2,w2;
  x1 = getRectangleX(r1);
  x2 = getRectangleX(r2);
  w1 = getRectangleWidth(r1);
  w2 = getRectangleWidth(r2);
  x1 = x1+w1;
  x2 = x2+w2;
  w1 = maiorDouble(x1,x2);
  return w1;
}

double maiorYplusH(Forma r1, Forma r2){
  double y1,h1,y2,h2;
  y1 = getRectangleY(r1);
  y2 = getRectangleY(r2);
  h1 = getRectangleHeight(r1);
  h2 = getRectangleHeight(r2);
  y1 = y1 + h1;
  y2 = y2 + h2;
  h1 = maiorDouble(y1,y2);
  return h1;
}

int verCircRect(Forma c, Forma r){
  double xr,yr,h,w,xc,yc,rc, aux1, aux2;
  double aux3,aux4,aux5,aux6;
  xr = getRectangleX(r);
  yr = getRectangleY(r);
  h = getRectangleHeight(r);
  w = getRectangleWidth(r);
  xc = getCircleX(c);
  yc = getCircleY(c);
  rc = getCircleRaio(c);
  aux1 = xr+w;
  aux2 = yr+h;
  aux3 = xc + rc;
  aux4 = xc - rc;
  aux5 = yc + rc;
  aux6 = yc - rc;
  if(verPointCirc(c,xr,yr))return 1;
  else if(verPointCirc(c,xr,aux2))return 1;
  else if(verPointCirc(c,aux1,yr))return 1;
  else if(verPointCirc(c,aux1,aux2))return 1;
  else if(verPointRect(r,xc,yc)) return 1;
  else if(verPointRect(r,xc,aux6))return 1;
  else if(verPointRect(r,xc,aux5))return 1;
  else if(verPointRect(r,aux4,yc))return 1;
  else if(verPointRect(r,aux3,yc))return 1;
  else return 0;
}

double getMaiorYCircRect(Forma c, Forma r){
  double h,yr,yc,rc;
  h = getRectangleHeight(r);
  yr = getRectangleY(r);
  yc = getCircleY(c);
  rc = getCircleRaio(c);
  yr = yr+h;
  yc = yc+rc;
  if(yr>yc)return yr;
  else return yc;
}

double getMaiorXCircRect(Forma c, Forma r){
  double w,xr,xc,rc;
  w = getRectangleWidth(r);
  xr = getRectangleX(r);
  xc = getCircleX(c);
  rc = getCircleRaio(c);
  xc += rc;
  xr += w;
  if(xc>xr) return xc;
  else return xr;
}

int verPontoInterno(Forma x,char tipo,double x2,double y2){
  double x1,y1;
  if(tipo=='c'){
    x1 = getCircleX(x);
    y1 = getCircleY(x);
    if(verPointCircInt(x,x2,y2))return 1;
    else return 0;
  }
  else{
    x1 = getRectangleX(x);
    y1 = getRectangleY(x);
    if(verPointRectInt(x,x2,y2)) return 1;
    else return 0;
  }
}

int verPointRectInt(Forma f, double x2, double y2){
  double x1, y1, h1, w1;
  x1 = getRectangleX(f);
  y1 = getRectangleY(f);
  h1 = getRectangleHeight(f);
  w1 = getRectangleWidth(f);
  if((x2>x1)&&(x2<(x1+w1))&&(y2>y1)&&(y2<(y1+h1))){
    return 1;
  }
  else return 0;
}

int verPointCircInt(Forma c, double x2, double y2){
  double x1,y1,r1, d;
  x1 = getCircleX(c);
  y1 = getCircleY(c);
  r1 = getCircleRaio(c);
  d = distanceBetweenPoints(x1,y1,x2,y2);
  if(d<r1)return 1;
  else return 0;
}

double verCentroMassa(Forma a, Forma b,char a1, char b1){
  double x1,y1,x2,y2, aux;
  x1 = getCentroX(a,a1);
  x2 = getCentroX(b,b1);
  y1 = getCentroY(a,a1);
  y2 = getCentroY(b,b1);
  aux = distanceBetweenPoints(x1,y1,x2,y2);
  return aux;
}

double getCentroX(Forma f,char c){
  double x,aux;
  if(c=='r'){
    x = getRectangleX(f);
    aux = getRectangleWidth(f);
    x = x + aux/2;
  }
  else x = getCircleX(f);
  return x;
}

double getCentroY(Forma f,char c){
  double y, aux;
  if(c=='r'){
    y = getRectangleY(f);
    aux = getRectangleHeight(f);
    y = y + aux/2;
  }
  else y = getCircleY(f);
  return y;
}



double getMenorXCircRect(Forma c, Forma r){
  double xC, xR, raio;
  raio = getCircleRaio(c);
  xC = getCircleX(c);
  xR = getRectangleX(r);
  xC -= raio;
  if(xC<xR) return xC;
  else return xR;
}

double getMenorYCircRect(Forma c, Forma r){
  double yC, yR, raio;
  yC = getCircleY(c);
  raio = getCircleRaio(c);
  yR = getRectangleY(r);
  yC -= raio;
  if(yC<yR) return yC;
  else return yR;
}

int verQuadraRet(Quadra q, Rect r){
  double x, y, larg, alt;
  x = getQuadraX(q);
  y = getQuadraY(q);
  larg = getQuadraW(q);
  alt = getQuadraH(q);
  if(verPointRect(r,x,y)&&verPointRect(r,x+larg,y)){
    if(verPointRect(r,x,y+alt)&&verPointRect(r,x+larg,y+alt)) return 1;
    else return 0;
  }
  else return 0;
}

int verQuadraCirc(Quadra q, Circle c){
  double x, y, larg, alt;
  int cond1, cond2, cond3, cond4;
  x = getQuadraX(q);
  y = getQuadraY(q);
  larg = getQuadraW(q);
  alt = getQuadraH(q);
  if(verPointCirc(c,x,y)&&verPointCirc(c,x+larg,y)) cond1 = 1;
  else cond1 = 0;
  if(verPointCirc(c,x,y+alt)&&verPointCirc(c,x+larg,y+alt)) cond2 = 1;
  else cond2 = 0;
  if(cond1&&cond2) return 1;
  else return 0;
}

Tree listToQuadtree(Lista l, getX gx, getY gy){
  Tree t;
  Pilha ch, aux;
  double x, y;
  t = quadtree_create();
  if(length(l)>0){
    ch = convexHull(l, gx, gy);
    while(getSizePilha(ch)>0){
      aux = pop(ch);
      x = gx(aux);
      y = gy(aux);
      quadtree_add(t,aux,x,y);
    }
  }
  return t;
}
