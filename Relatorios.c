#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Relatorios.h"
#include "Pilha.h"
#include "ConvexHull.h"
#include "Quadtree.h"
#include "Torre.h"

#define PI 3.1415926

void empilhaTorres(Posic node, Rect r, Tree t, Pilha p);
void imprimeTorreSvg(FILE *arq, Torre t);
void imprimePoligonoCobertura(FILE *arq, Pilha p);

void coberturaTorres(Cidade cid, Rect r, char *nomePadrao,char *nomeQry ,char *dirBSD, char *sufixo){
  int size, i, j, divisoes, ind;
  double aux, raio,x ,y;
  char *nomeFinal;
  getX gx;
  getY gy;
  Pilha torres, ch;
  Tree treeTorres;
  Torre t,save;
  Lista list;
  vectorNode *ponto, *antes, *atual, *primeiro;
  FILE *arq;
  Rect testeRetangulo;
  /*NUMERO DE DIVISOES DO PERIMETRO DO CIRCULO*/
  divisoes = 8;
  treeTorres = getTorresTree(cid);
  torres = createPilha();
  empilhaTorres(quadtree_getRoot(treeTorres),r,treeTorres,torres);
  size = getSizePilha(torres);
  openArchAreaTorres(dirBSD,nomePadrao, nomeQry, sufixo,cid);
  arq = getArchAreaTorres(cid);
  if(size>0){
    save = createPilha();
    ponto = malloc(sizeof(vectorNode)*size*divisoes);
    ind = 0;
    for(i=0;i<size;i++){
      aux = 2*PI/divisoes;
      t = pop(torres);
      raio = getTorreRaio(t);
      x = getTorreX(t);
      y = getTorreY(t);
      if(raio!=0){
        for(j=0;j<divisoes;j++){
          ponto[ind].x = cos(aux)*raio + x;
          ponto[ind].y = sin(aux)*raio + y;
          ponto[ind].ang = -1;
          ponto[ind].ptr = NULL;
          aux = aux + (2*PI/divisoes);
          ind++;
        }
      }
      else{
        ponto[ind].x = x;
        ponto[ind].y = y;
        ponto[ind].ang = -1;
        ponto[ind].ptr = NULL;
        ind++;
      }

      push(save,t);
    }
    /*ATE AQUI TEMOS O VETOR PONTO, QUE POSSUI OS PONTOS DA CONVEXHULL EM FORMA DE
     VECTORNODE, E A PILHA SAVE, QUE TEM AS TORRES QUE ESTAO DENTRO DO RETANGULO.
     */
     arq = getArchAreaTorres(cid);
     imprimeQuadrasSvg(cid,arq);
     imprimeHidrantesSvg(cid,arq);
     imprimeSemaforosSvg(cid,arq);
     imprimeTorresSvg(cid,arq);
     size = getSizePilha(save);
     for(i=0;i<size;i++){
      t = pop(save);
      /*imprimeTorreSvg(arq,pop(save));*/
      fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"%f\"", getTorreX(t),getTorreY(t),getTorreRaio(t));
      fprintf(arq," fill=\"magenta\" stroke=\"black\" stroke-width=\"2\" fill-opacity=\"0.4\"/>\n");
      fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">", getTorreX(t), getTorreY(t));
      fprintf(arq,"%s</text>\n",getTorreId(t));
      }
      ind--;
      ch = createPilha();
      size *= 8;
      iniciaVetor(ponto, ind);
      calculaAngulos(ponto, ind);
      quicksort(ponto,1,ind-1);
      arrumaAngulosIguais(ponto,ind);
      calculaConvexHull(ponto,ind,ch,torres);
      /*imprimePoligonoCobertura(arq,save);*/
      size = getSizePilha(ch);
      if(size>1){
        printf("\nSize:%d",size);
        antes = pop(ch);
        primeiro = antes;
        for(i=1;i<size;i++){
          x = antes->x;
          y = antes->y;
          atual = pop(ch);
          /*ponto = pop(ch);*/
          /*fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"10\"", x,y);
          fprintf(arq," fill=\"blue\" stroke=\"black\" stroke-width=\"2\" fill-opacity=\"0.4\"/>\n");*/
          fprintf(arq,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"", x, y,atual->x,atual->y);
          fprintf(arq," style=\"stroke:black;stroke-width:2\"/>\n");
          antes = atual;
        }
        fprintf(arq,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"",atual->x,atual->y,primeiro->x,primeiro->y);
        fprintf(arq," style=\"stroke:black;stroke-width:2\"/>\n");
       }
    }
    closeArchAreaTorres(cid);

}

void empilhaTorres(Posic node, Rect r, Tree t, Pilha p){
  Torre aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointRectInt(r,getTorreX(aux),getTorreY(aux)))
      push(p,aux);
    empilhaTorres(quadtree_getNodeNE(t, node),r,t,p);
    empilhaTorres(quadtree_getNodeNW(t, node),r,t,p);
    empilhaTorres(quadtree_getNodeSE(t, node),r,t,p);
    empilhaTorres(quadtree_getNodeSW(t, node),r,t,p);
  }
}

void imprimeTorreSvg(FILE *arq, Torre t){
  double x, y, raio;
  x = getTorreX(t);
  y = getTorreY(t);
  raio = getTorreRaio(t);
  /*fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"%f\"", x, y, raio);
  fprintf(arq," fill=\"magenta\" stroke=\"black\" stroke-width=\"2\" fill-opacity=\"0.4\"/>\n");*/
}

void imprimePoligonoCobertura(FILE *arq, Pilha p){
  int size,i;
  vectorNode *v,*ini;
  size = getSizePilha(p);
  if(size>1){
    ini = pop(p);
    for(i=0;i<size;i++){
      v = pop(p);
      fprintf(arq,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"",ini->x,ini->y,v->x,v->y);
      fprintf(arq," style=\"stroke:black;stroke-width:2\"/>\n");
      ini = v;
    }
  }
}
