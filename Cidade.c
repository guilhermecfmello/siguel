#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Cidade.h"
#include "Escrita.h"
#include "Dicionario.h"
#include "Hash.h"
#include "Grafo.h"

#define INFINITO 1.7*pow(10,307)

typedef struct _cidade{
  Lista qua;
  Lista hid;
  Lista sem;
  Lista tor;
  Dicionario dici;
  Grafo vias;/*Grafo contendo as vidas da cidade*/
  Tree tQua;/*Quadtree com os elementos da cidade*/
  Tree tHid;/*Quadtree com os elementos da cidade*/
  Tree tSem;/*Quadtree com os elementos da cidade*/
  Tree tTor;/*Quadtree com os elementos da cidade*/
  FILE *saiSvg;/*ARQUIVO DE SAIDA EM FORMATO SVG, CONTEM O MAPA DA CIDADE*/
  FILE *saiTxtConsultas;/*ARQUIVO DE SAIDA TXT, DESCRICAO DAS CONSULTAS FEITAS*/
  FILE *saiTxtComp;/*ARQUIVO DE SAIDA TXT, O NUMERO DE COMPARACOES PARA INSERCAO/REMOCAO DA LISTA*/
  FILE *entGeo;/*ARQUIVO DE ENTRADA, ARQUIVO .GEO QUE CONTEM OS ELEMENTOS DA CIDADE.*/
  FILE *entQry;/*ARQUIVO DE ENTRADA, ARQUIVO .QRY QUE CONTEM INSTRUCOES DE EXCLUSAO DE ITENS*/
  FILE *entPm;/*ARQUIVO DE ENTRADA, LEITURA E CRIACAO DE PESSOAS*/
  FILE *entTm;/*ARQUIVO DE ENTRADA, DETERMINAR PESSOAS E SUAS RESPECTIVAS LINHAS MOVEIS*/
  FILE *entEc;/*ARQUIVO DE ENTRADA, LEITURA E CRIACAO DE ESTABELECIMENTOS COMERCIAIS*/
  FILE *areaTorres;/*ARQUIVO DE SAIDA, SVG QUE MOSTRA A CIDADE, A AREA DE COBERTURA DAS TORRES E SEU ENVOLTORIO CONVEXO*/
  FILE *entVia;/*ARQUIVO DE ENTRADA, LEITURA DAS VIAS DA CIDADE*/
  FILE *saiSvgVias; /*ARQUIVO DE SAIDA, NELE SERA IMPRESSO O MAPA DA CIDADE COM OS CAMINHOS CONSULTADOS PELO QRY.*/
  char *cfillQuadras;
  char *cstrkQuadras;
  char *cfillHidrantes;
  char *cstrkHidrantes;
  char *cfillSemaforos;
  char *cstrkSemaforos;
  char *cfillTorres;
  char *cstrkTorres;
  int numQuadras;
}cidade;

Cidade createCidade(){
  cidade *c = (cidade*)(malloc(sizeof(cidade)));
  c->qua = createList();
  c->hid = createList();
  c->sem = createList();
  c->tor = createList();
  c->tQua = quadtree_create();
  c->tHid = quadtree_create();
  c->tSem = quadtree_create();
  c->tTor = quadtree_create();
  c->dici = dicionario_create();
  c->vias = grafo_create(31);
  c->saiSvg = NULL;
  c->saiTxtConsultas = NULL;
  c->saiTxtComp = NULL;
  c->entGeo = NULL;
  c->entQry = NULL;
  c->entPm = NULL;
  c->entTm = NULL;
  c->entEc = NULL;
  c->entVia = NULL;
  c->saiSvgVias = NULL;
  c->areaTorres = NULL;
  c->cfillQuadras = NULL;
  c->cfillHidrantes = NULL;
  c->cfillSemaforos = NULL;
  c->cfillTorres = NULL;
  c->cstrkQuadras = NULL;
  c->cstrkHidrantes = NULL;
  c->cstrkSemaforos = NULL;
  c->cstrkTorres = NULL;
  c->numQuadras = 0;
  return (Cidade)c;
}



Quadra insereQuadra(Cidade c, Quadra q){
  cidade *cid = (cidade*) c;
  insert(cid->qua,q);
  cid->numQuadras++;
  return q;
}

Hidrante insereHidrante(Cidade c, Hidrante h){
  cidade *cid = (cidade*) c;
  insert(cid->hid, h);
  return h;
}

Semaforo insereSemaforo(Cidade c, Semaforo s){
  cidade *cid = (cidade*) c;
  insert(cid->sem, s);
  return s;
}

Torre insereTorre(Cidade c, Torre t){
  cidade *cid = (cidade*) c;
  insert(cid->tor, t);
  return t;
}


void setCoresQuadras(Cidade c, char *cfill, char *cstrk){
  cidade *cid = (cidade*) c;
  if(cid->cfillQuadras!=NULL){
    free(cid->cfillQuadras);
    free(cid->cstrkQuadras);
  }
  cid->cfillQuadras = malloc(sizeof(char)*(strlen(cfill)+1));
  cid->cstrkQuadras = malloc(sizeof(char)*(strlen(cstrk)+1));
  strcpy(cid->cfillQuadras,cfill);
  strcpy(cid->cstrkQuadras,cstrk);
}

void setCoresHidrantes(Cidade c, char *cfill, char *cstrk){
  cidade *cid = (cidade*) c;
  if(cid->cfillHidrantes!=NULL){
    free(cid->cfillHidrantes);
    free(cid->cstrkHidrantes);
  }
  cid->cfillHidrantes = malloc(sizeof(char)*(strlen(cfill)+1));
  cid->cstrkHidrantes = malloc(sizeof(char)*(strlen(cstrk)+1));
  strcpy(cid->cfillHidrantes, cfill);
  strcpy(cid->cstrkHidrantes, cstrk);
}

void setCoresTorres(Cidade c, char *cfill, char *cstrk){
  cidade *cid = (cidade*) c;
  if(cid->cfillTorres!=NULL){
    free(cid->cfillTorres);
    free(cid->cstrkTorres);
  }
  cid->cfillTorres = malloc(sizeof(char)*(strlen(cfill)+1));
  cid->cstrkTorres = malloc(sizeof(char)*(strlen(cstrk)+1));
  strcpy(cid->cfillTorres, cfill);
  strcpy(cid->cstrkTorres, cstrk);
}

void setCoresSemaforos(Cidade c, char *cfill, char *cstrk){
  cidade *cid = (cidade*) c;
  if(cid->cfillSemaforos!=NULL){
    free(cid->cfillSemaforos);
    free(cid->cstrkSemaforos);
  }
  cid->cfillSemaforos = malloc(sizeof(char)*(strlen(cfill)+1));
  cid->cstrkSemaforos = malloc(sizeof(char)*(strlen(cstrk)+1));
  strcpy(cid->cfillSemaforos,cfill);
  strcpy(cid->cstrkSemaforos,cstrk);
}

void imprimeQuadrasSvgRecursive(Cidade c, Tree t, Posic aux, FILE *arq){
  Posic content;
  cidade *cid = (cidade*) c;
  double x, y, w, h;
  char *cep;
  if(aux!=NULL){
    imprimeQuadrasSvgRecursive(c,t, quadtree_getNodeNE(t, aux),arq);
    imprimeQuadrasSvgRecursive(c,t, quadtree_getNodeNW(t, aux),arq);
    imprimeQuadrasSvgRecursive(c,t, quadtree_getNodeSE(t, aux),arq);
    imprimeQuadrasSvgRecursive(c,t, quadtree_getNodeSW(t, aux),arq);
    content = quadtree_get(aux);
    x = getQuadraX(content);
    y = getQuadraY(content);
    w = getQuadraW(content);
    h = getQuadraH(content);
    cep = getQuadraCep(content);
    fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\"", x, y, w, h);
    fprintf(arq," fill=\"%s\" stroke=\"%s\" stroke-width=\"2\"/>\n", cid->cfillQuadras, cid->cstrkQuadras);
    x += 6;
    y += 25;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">", x, y);
    fprintf(arq,"%s</text>\n",cep);
  }
}
void imprimeHidrantesSvgRecursive(Cidade c, Tree t, Posic aux, FILE *arq){
  double x, y;
  Posic content;
  cidade *cid = (cidade*) c;
  if(aux!=NULL){
    imprimeHidrantesSvgRecursive(c,t, quadtree_getNodeNE(t, aux),arq);
    imprimeHidrantesSvgRecursive(c,t, quadtree_getNodeNW(t, aux),arq);
    imprimeHidrantesSvgRecursive(c,t, quadtree_getNodeSE(t, aux),arq);
    imprimeHidrantesSvgRecursive(c,t, quadtree_getNodeSW(t, aux),arq);
    content = quadtree_get(aux);
    x = getHidranteX(content);
    y = getHidranteY(content);
    fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"10\"",x,y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>\n",cid->cfillHidrantes, cid->cstrkHidrantes);
    x -= 5;
    y += 5;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">H</text>\n",x,y);
  }
}

void imprimeSemaforosSvgRecursive(Cidade c, Tree t, Posic aux, FILE *arq){
  Posic content;
  cidade *cid = (cidade*) c;
  double x, y;
  if(aux!=NULL){
    imprimeSemaforosSvgRecursive(c,t, quadtree_getNodeNE(t, aux),arq);
    imprimeSemaforosSvgRecursive(c,t, quadtree_getNodeNW(t, aux),arq);
    imprimeSemaforosSvgRecursive(c,t, quadtree_getNodeSE(t, aux),arq);
    imprimeSemaforosSvgRecursive(c,t, quadtree_getNodeSW(t, aux),arq);
    content = quadtree_get(aux);
    x = getSemaforoX(content);
    y = getSemaforoY(content);
    fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"10\" height=\"20\"",x,y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>\n",cid->cfillSemaforos,cid->cstrkSemaforos);
    y = y + 10;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">S</text>\n",x,y);
  }
}

void imprimeTorresSvgRecursive(Cidade c, Tree t, Posic aux, FILE *arq){
  Posic content;
  cidade *cid = (cidade*) c;
  double x, y;
  if(aux!=NULL){
    imprimeTorresSvgRecursive(c,t, quadtree_getNodeNE(t, aux),arq);
    imprimeTorresSvgRecursive(c,t, quadtree_getNodeNW(t, aux),arq);
    imprimeTorresSvgRecursive(c,t, quadtree_getNodeSE(t, aux),arq);
    imprimeTorresSvgRecursive(c,t, quadtree_getNodeSW(t, aux),arq);
    content = quadtree_get(aux);
    x = getTorreX(content);
    y = getTorreY(content);
    fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"10\"", x, y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>",cid->cfillTorres, cid->cstrkTorres);
    x -= 5;
    y += 5;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">T</text>\n",++x,++y);
  }
}

void imprimeQuadrasSvg(Cidade c, FILE *arq){
    cidade *cid = (cidade*) c;
    Posic aux;
    aux = quadtree_getRoot(cid->tQua);
    imprimeQuadrasSvgRecursive(c,cid->tQua,aux,arq);
}

void imprimeHidrantesSvg(Cidade c, FILE *arq){
  cidade *cid = (cidade*) c;
  Posic aux;
  aux = quadtree_getRoot(cid->tHid);
  imprimeHidrantesSvgRecursive(c,cid->tHid,aux,arq);
  /*double x, y;
  Posic aux, content;
  FILE *arq;
  cidade *cid = (cidade*) c;
  arq = getArchSvg(c);
  aux = getFirst(cid->hid);
  while(aux!=NULL){
    content = get(cid->hid,aux);
    x = getHidranteX(content);
    y = getHidranteY(content);
    fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"10\"",x,y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>\n",cid->cfillHidrantes, cid->cstrkHidrantes);
    x -= 5;
    y += 5;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">H</text>\n",x,y);
    aux = getNext(cid->hid, aux);
  }*/
}

void imprimeSemaforosSvg(Cidade c, FILE *arq){
  cidade *cid = (cidade*) c;
  Posic aux;
  aux = quadtree_getRoot(cid->tSem);
  imprimeSemaforosSvgRecursive(c,cid->tSem,aux,arq);
  /*int i;
  double x, y;
  Posic aux;
  Semaforo content;
  FILE *arq;
  cidade *cid = NULL;
  cid = (cidade*) c;
  arq = getArchSvg(c);
  aux = getFirst(cid->sem);
  i = 0;
  while(aux!=NULL){
    content = get(cid->sem,aux);
    x = getSemaforoX(content);
    y = getSemaforoY(content);
    fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"10\" height=\"20\"",x,y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>\n",cid->cfillSemaforos,cid->cstrkSemaforos);
    y = y + 10;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">S</text>\n",x,y);
    aux = getNext(cid->sem,aux);
  }*/
}

void imprimeTorresSvg(Cidade c, FILE *arq){
  cidade *cid = (cidade*) c;
  Posic aux;
  aux = quadtree_getRoot(cid->tTor);
  imprimeTorresSvgRecursive(c,cid->tTor,aux,arq);
  /*double x, y;
  Posic aux, content;
  FILE *arq;
  cidade *cid = (cidade*) c;
  arq = getArchSvg(c);
  aux = getFirst(cid->tor);
  while(aux!=NULL){
    content = get(cid->tor, aux);
    x = getTorreX(content);
    y = getTorreY(content);
    fprintf(arq," <circle cx=\"%f\" cy=\"%f\" r=\"10\"", x, y);
    fprintf(arq," fill=\"%s\" stroke=\"%s\"/>",cid->cfillTorres, cid->cstrkTorres);
    x -= 5;
    y += 5;
    fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">T</text>\n",++x,++y);
    aux = getNext(cid->sem,aux);
  }*/
}



int getNumQuadras(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->numQuadras;
}

/*Quadra getQuadraRet(Cidade c, Rect r, int *comp){
  cidade *cid = (cidade*) c;
  Quadra aux;
  Posic node = getFirst(cid->qua);
  while(node!=NULL){
    *comp = *comp + 1;
    aux = get(cid->qua,node);
    if(verQuadraRet(aux,r)) return node;
    node = getNext(cid->qua,node);
  }
  return NULL;
}

Quadra getQuadraCirc(Cidade c, Circle circ, int *comp){
  cidade *cid = (cidade*) c;
  Quadra aux;
  Posic node = getFirst(cid->qua);
  while(node!=NULL){
    *comp = *comp + 1;
    aux = get(cid->qua,node);
    if(verQuadraCirc(aux,circ))return node;
    node = getNext(cid->qua,node);
  }
  return NULL;
}
*/


void getQuadraRetRecursive(Posic node, Rect r, Tree t, Quadra *q);

void getQuadraCircRecursive(Posic node, Circle c, Tree t, Quadra *q);

void getHidranteRetRecursive(Posic node, Rect r, Tree t, Hidrante *h);

void getHidranteCircRecursive(Posic node, Circle c, Tree t, Hidrante *h);

void getSemaforoRetRecursive(Posic node, Rect r, Tree t, Semaforo *s);

void getSemaforoCircRecursive(Posic node, Circle c, Tree t, Semaforo *s);

void getTorreCircRecursive(Posic node, Circle c, Tree t, Torre *tor);

void getTorreRetRecursive(Posic node, Rect r, Tree t, Torre *tor);




Quadra getQuadraRet(Cidade cid,Rect r){
  cidade *c = (cidade*) cid;
  Quadra aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(c->tQua);
  getQuadraRetRecursive(node,r,c->tQua, &aux);
  return aux;
}
Quadra getQuadraCirc(Cidade c,Circle circ){
  cidade *cid = (cidade*) c;
  Quadra aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tQua);
  getQuadraCircRecursive(node,circ,cid->tQua, &aux);
  return aux;
}


Hidrante getHidranteRet(Cidade c, Rect r){
  cidade *cid = (cidade*) c;
  Hidrante aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tHid);
  getHidranteRetRecursive(node,r,cid->tHid, &aux);
  return aux;
}

Hidrante getHidranteCirc(Cidade c, Circle circ){
  cidade *cid = (cidade*) c;
  Hidrante aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tHid);
  getHidranteCircRecursive(node,circ,cid->tHid, &aux);
  return aux;
}

Semaforo getSemaforoRet(Cidade c, Rect r){
  cidade *cid = (cidade*) c;
  Semaforo aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tSem);
  getSemaforoRetRecursive(node,r,cid->tSem, &aux);
  return aux;
}



Semaforo getSemaforoCirc(Cidade c, Circle circ){
  cidade *cid = (cidade*) c;
  Semaforo aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tSem);
  getSemaforoCircRecursive(node,circ,cid->tSem, &aux);
  return aux;
}


Torre getTorreRet(Cidade c, Rect r){
  cidade *cid = (cidade*) c;
  Torre aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tTor);
  getTorreRetRecursive(node,r,cid->tTor, &aux);
  return aux;
}

Torre getTorreCirc(Cidade c, Circle circ){
  cidade *cid = (cidade*) c;
  Torre aux;
  Posic node;
  aux = NULL;
  node = quadtree_getRoot(cid->tTor);
  getTorreCircRecursive(node,circ,cid->tTor, &aux);
  return aux;
}

void removeQuadra(Cidade c, Quadra q){
  cidade *cid = (cidade*) c;

  quadtree_remove(cid->tQua,q);
}

void removeHidrante(Cidade c, Hidrante h){
  cidade *cid = (cidade*) c;
  quadtree_remove(cid->tHid,h);
}

void removeSemaforo(Cidade c, Semaforo s){
  cidade *cid = (cidade*) c;
  quadtree_remove(cid->tSem,s);
}

void removeTorre(Cidade c, Torre t){
  cidade *cid = (cidade*) c;
  quadtree_remove(cid->tTor,t);
}

void procuraQuadraRecursive(Posic node, Tree t, Quadra *q, char *end){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(strcmp(getQuadraCep(aux),end)==0){
      *q = node;
    }
    procuraQuadraRecursive(quadtree_getNodeNE(t, node),t,q,end);
    procuraQuadraRecursive(quadtree_getNodeNW(t, node),t,q,end);
    procuraQuadraRecursive(quadtree_getNodeSE(t, node),t,q,end);
    procuraQuadraRecursive(quadtree_getNodeSW(t, node),t,q,end);
  }
}

Quadra procuraQuadra(Cidade c, char *end){
  Quadra qua;
  cidade *cid = (cidade*) c;
  qua = NULL;
  procuraQuadraRecursive(quadtree_getRoot(cid->tQua),cid->tQua,&qua,end);
  return qua;
}
/*char *cep;
cidade *cid = (cidade*) c;
Posic node;
Quadra aux;
node = getFirst(cid->qua);
while(node!=NULL){
aux = get(cid->qua, node);
cep = getQuadraCep(aux);
if(strcmp(cep,end)==0) return aux;
node = getNext(cid->qua, node);
}
return NULL;*/
void procuraHidranteRecursive(Posic node, Tree t, Hidrante *h, char *end){
  Hidrante aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(strcmp(getHidranteId(aux),end)==0)
      *h = node;
    procuraHidranteRecursive(quadtree_getNodeNE(t, node),t,h,end);
    procuraHidranteRecursive(quadtree_getNodeNW(t, node),t,h,end);
    procuraHidranteRecursive(quadtree_getNodeSE(t, node),t,h,end);
    procuraHidranteRecursive(quadtree_getNodeSW(t, node),t,h,end);
  }
}

Hidrante procuraHidrante(Cidade c, char *end){
  Hidrante hid;
  cidade *cid = (cidade*) c;
  hid = NULL;
  procuraHidranteRecursive(quadtree_getRoot(cid->tHid),cid->tHid,&hid,end);
  return hid;
}

void procuraSemaforoRecursive(Posic node, Tree t, Semaforo *s, char *end){
  Semaforo aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(strcmp(getSemaforoId(aux),end)==0)
      *s = node;
    procuraSemaforoRecursive(quadtree_getNodeNE(t, node),t,s,end);
    procuraSemaforoRecursive(quadtree_getNodeNW(t, node),t,s,end);
    procuraSemaforoRecursive(quadtree_getNodeSE(t, node),t,s,end);
    procuraSemaforoRecursive(quadtree_getNodeSW(t, node),t,s,end);
  }
}

Semaforo procuraSemaforo(Cidade c, char *end){
  Semaforo sem;
  cidade *cid = (cidade*) c;
  sem = NULL;
  procuraSemaforoRecursive(quadtree_getRoot(cid->tSem),cid->tSem,&sem,end);
  return sem;
}

void procuraTorreRecursive(Posic node, Tree t, Torre *tor, char *end){
  Semaforo aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(strcmp(getTorreId(aux),end)==0)
      *tor = node;
    procuraTorreRecursive(quadtree_getNodeNE(t, node),t,tor,end);
    procuraTorreRecursive(quadtree_getNodeNW(t, node),t,tor,end);
    procuraTorreRecursive(quadtree_getNodeSE(t, node),t,tor,end);
    procuraTorreRecursive(quadtree_getNodeSW(t, node),t,tor,end);
  }
}

Torre procuraTorreList(Cidade c, char *end){
  int i, size;
  Torre t;
  Lista l;
  cidade *cid;
  cid = (cidade*) c;
  size = length(cid->tor);
  if(size>0){
    l = getFirst(cid->tor);
    do{
      t = get(cid->tor,l);
      if(strcmp(getTorreId(t),end)==0)
        return t;
      size--;
      l = getNext(cid->tor,l);
    }while(size>0);
  }
  return NULL;
}

Torre procuraTorre(Cidade c, char *end){
  Torre tor;
  cidade *cid = (cidade*) c;
  tor = NULL;
  procuraTorreRecursive(quadtree_getRoot(cid->tTor),cid->tTor,&tor,end);
  return tor;
}

Posic procuraElemento(Cidade c, char *end, char *typeElement){
  Posic obj;
  obj = procuraQuadra(c,end);
  if(obj!=NULL){
    *typeElement = 'q';
    return obj;
  }
  obj = procuraHidrante(c,end);
  if(obj!=NULL){
    *typeElement = 'h';
    return obj;
  }
  obj = procuraSemaforo(c,end);
  if(obj!=NULL){
    *typeElement = 's';
    return obj;
  }
  obj = procuraTorre(c,end);
  if(obj!=NULL){
    *typeElement = 't';
    return obj;
  }
  *typeElement = 'x';
  return NULL;
}


void openArchAreaTorres(char *patch, char *nome, char *nomeQry2, char *sufixo,Cidade c){
    char *nomeCompleto, *nomeQry;
    cidade *cid = (cidade*) c;
    nomeQry = filtraNome(nomeQry2);
    if(patch!=NULL){
      nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+strlen(nomeQry)+strlen(sufixo)+7));
      sprintf(nomeCompleto,"%s%s-%s-%s.svg",patch ,nome, nomeQry,sufixo);
      cid->areaTorres = fopen(nomeCompleto,"w");
    }
    else{
      nomeCompleto = malloc(sizeof(char)*(strlen(nome)+strlen(nomeQry)+strlen(sufixo)+7));
      sprintf(nomeCompleto,"%s-%s-%s.svg", nome, nomeQry,sufixo);
      cid->areaTorres = fopen(nomeCompleto,"w");
    }
    if(cid->areaTorres==NULL)
      printf("ERRO NA ABERTURA DO ARQUIVO DE COBERTURA DE TORRES");
    else
      fprintf(cid->areaTorres,"<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void openArchSvg(char *patch, char *nome, char *qry, Cidade c){
  char *nomeCompleto;
  cidade *cid = (cidade*) c;

  if(qry==NULL){
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
    sprintf(nomeCompleto,"%s%s.svg",patch,nome);
  }
  else{
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+strlen(qry)+6));
    sprintf(nomeCompleto,"%s%s-%s.svg",patch,nome,qry);
  }
  cid->saiSvg = fopen(nomeCompleto,"w");


  if(cid->saiSvg==NULL)
    printf("\n####DEU RUIM NA ABERTURA DO SVG\n");
  fprintf(cid->saiSvg,"<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void openArchTxtCons(char *patch, char *nome, char *qry, Cidade c){
  char *nomeCompleto;
  cidade *cid = (cidade*) c;
  if(qry==NULL){
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
    sprintf(nomeCompleto,"%s%s.txt",patch,nome);
  }
  else{
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+strlen(qry)+6));
    sprintf(nomeCompleto,"%s%s-%s.txt",patch,nome,qry);
  }
  cid->saiTxtConsultas = fopen(nomeCompleto, "w");
}

void openArchTxtComp(char *patch, char *nome, char *type, Cidade c){
  char *nomeCompleto;
  cidade *cid = (cidade*) c;
  nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
  sprintf(nomeCompleto,"%s%s.txt",patch,nome);
  cid->saiTxtComp = fopen(nomeCompleto,type);
}

void openArchGeo(char *patch, char *nome, Cidade c){
  char *nomeCompleto;
  cidade *cid = (cidade*) c;
  if(patch!=NULL){
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
    sprintf(nomeCompleto,"%s%s",patch,nome);
  }
  else{
    nomeCompleto = malloc(sizeof(char)*(strlen(nome)+5));
    sprintf(nomeCompleto,"%s",nome);
  }
  cid->entGeo = fopen(nomeCompleto,"r");
  if(cid->entGeo==NULL)
    printf("\n###DEU RUIM NA ABERTURA DO ARQUIVO GEO");
}

void openArchQry(char *patch, char *nome, Cidade c){
  char *nomeCompleto;
  cidade *cid = (cidade*) c;
  if(nome!=NULL){
    if(patch!=NULL){
      nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
      sprintf(nomeCompleto,"%s%s",patch,nome);
    }
    else{
      nomeCompleto = malloc(sizeof(char)*(strlen(nome)+5));
      sprintf(nomeCompleto,"%s",nome);
    }
    cid->entQry = fopen(nomeCompleto,"r");
  }
}
void closeArchAreaTorres(Cidade c){
  cidade *cid = (cidade*) c;
  if(cid->areaTorres!=NULL){
    fprintf(cid->areaTorres,"</svg>\n");
    fclose(cid->areaTorres);
  }
}

void closeArchSvg(Cidade c){
  cidade *cid = (cidade*) c;
  fprintf(cid->saiSvg,"</svg>\n");
  if(cid->saiSvg!=NULL) fclose(cid->saiSvg);
}

void closeArchTxtCons(Cidade c){
  cidade *cid = (cidade*) c;
  if(cid->saiTxtConsultas!=NULL) fclose(cid->saiTxtConsultas);
}

void closeArchTxtComp(Cidade c){
  cidade *cid = (cidade*) c;
  if(cid->saiTxtComp!=NULL) fclose(cid->saiTxtComp);
}

void closeArchQry(Cidade c){
  cidade *cid = (cidade*) c;
  if(cid->entQry!=NULL) fclose(cid->entQry);
}

void closeArchGeo(Cidade c){
  cidade *cid = (cidade*) c;
  if(cid->entGeo!=NULL) fclose(cid->entGeo);
}


FILE *getArchGeo(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->entGeo;
}

FILE *getArchTxtCons(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->saiTxtConsultas;
}

FILE *getArchTxtComp(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->saiTxtComp;
}

FILE *getArchQry(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->entQry;
}

FILE *getArchAreaTorres(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->areaTorres;
}

FILE *getArchSvg(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->saiSvg;
}

Quadra getQuadrasList(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->qua;
}

Torre getTorresList(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->tor;
}

Semaforo getSemaforosList(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->sem;
}

Hidrante getHidrantesList(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->hid;
}

Tree setQuadrasQuadTree(Cidade cid, Tree t){
  cidade *c = (cidade*) cid;
  c->tQua = t;
  return c->tQua;
}

Tree setSemaforosQuadTree(Cidade cid, Tree t){
  cidade *c = (cidade*) cid;
  c->tSem = t;
  return c->tSem;
}

Tree setHidrantesQuadTree(Cidade cid, Tree t){
  cidade *c = (cidade*) cid;
  c->tHid = t;
  return c->tHid;
}

Tree setTorresQuadTree(Cidade cid, Tree t){
  cidade *c = (cidade*) cid;
  c->tTor = t;
  return c->tTor;
}

void getTorreCircRecursive(Posic node, Circle c, Tree t, Torre *tor){
  Torre aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointCircInt(c,getTorreX(aux),getTorreY(aux)))
      *tor = node;
    getTorreCircRecursive(quadtree_getNodeNE(t, node),c,t,tor);
    getTorreCircRecursive(quadtree_getNodeNW(t, node),c,t,tor);
    getTorreCircRecursive(quadtree_getNodeSE(t, node),c,t,tor);
    getTorreCircRecursive(quadtree_getNodeSW(t, node),c,t,tor);
  }
}

void getTorreRetRecursive(Posic node, Rect r, Tree t, Torre *tor){
  Torre aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointRectInt(r,getTorreX(aux),getTorreY(aux)))
      *tor = node;
    getTorreRetRecursive(quadtree_getNodeNE(t, node),r,t,tor);
    getTorreRetRecursive(quadtree_getNodeNW(t, node),r,t,tor);
    getTorreRetRecursive(quadtree_getNodeSE(t, node),r,t,tor);
    getTorreRetRecursive(quadtree_getNodeSW(t, node),r,t,tor);
  }
}

void getSemaforoRetRecursive(Posic node, Rect r, Tree t, Semaforo *s){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointRectInt(r,getSemaforoX(aux),getSemaforoY(aux)))
      *s = node;
    getSemaforoRetRecursive(quadtree_getNodeNE(t, node),r,t,s);
    getSemaforoRetRecursive(quadtree_getNodeNW(t, node),r,t,s);
    getSemaforoRetRecursive(quadtree_getNodeSE(t, node),r,t,s);
    getSemaforoRetRecursive(quadtree_getNodeSW(t, node),r,t,s);
  }
}
void getSemaforoCircRecursive(Posic node, Circle c, Tree t, Semaforo *s){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointCircInt(c,getSemaforoX(aux),getSemaforoY(aux)))
      *s = node;
    getSemaforoCircRecursive(quadtree_getNodeNE(t, node),c,t,s);
    getSemaforoCircRecursive(quadtree_getNodeNW(t, node),c,t,s);
    getSemaforoCircRecursive(quadtree_getNodeSE(t, node),c,t,s);
    getSemaforoCircRecursive(quadtree_getNodeSW(t, node),c,t,s);
  }
}
void getHidranteRetRecursive(Posic node, Rect r, Tree t, Hidrante *h){
  Hidrante aux;
  if(node!=NULL){
    aux = quadtree_get(node);

    if(verPointRectInt(r,getHidranteX(aux),getHidranteY(aux)))
      *h = node;
    getHidranteRetRecursive(quadtree_getNodeNE(t, node),r,t,h);
    getHidranteRetRecursive(quadtree_getNodeNW(t, node),r,t,h);
    getHidranteRetRecursive(quadtree_getNodeSE(t, node),r,t,h);
    getHidranteRetRecursive(quadtree_getNodeSW(t, node),r,t,h);
  }
}
void getHidranteCircRecursive(Posic node, Circle c, Tree t, Hidrante *h){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verPointCircInt(c,getHidranteX(aux),getHidranteY(aux)))
      *h = node;
    getHidranteCircRecursive(quadtree_getNodeNE(t, node),c,t,h);
    getHidranteCircRecursive(quadtree_getNodeNW(t, node),c,t,h);
    getHidranteCircRecursive(quadtree_getNodeSE(t, node),c,t,h);
    getHidranteCircRecursive(quadtree_getNodeSW(t, node),c,t,h);
  }
}

void getQuadraRetRecursive(Posic node, Rect r, Tree t, Quadra *q){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verQuadraRet(aux,r))
      *q = node;
    getQuadraRetRecursive(quadtree_getNodeNE(t, node),r,t,q);
    getQuadraRetRecursive(quadtree_getNodeNW(t, node),r,t,q);
    getQuadraRetRecursive(quadtree_getNodeSE(t, node),r,t,q);
    getQuadraRetRecursive(quadtree_getNodeSW(t, node),r,t,q);
  }
}
void getQuadraCircRecursive(Posic node, Circle c, Tree t, Quadra *q){
  Quadra aux;
  if(node!=NULL){
    aux = quadtree_get(node);
    if(verQuadraCirc(aux,c))
      *q = node;
    getQuadraCircRecursive(quadtree_getNodeNE(t, node),c,t,q);
    getQuadraCircRecursive(quadtree_getNodeNW(t, node),c,t,q);
    getQuadraCircRecursive(quadtree_getNodeSE(t, node),c,t,q);
    getQuadraCircRecursive(quadtree_getNodeSW(t, node),c,t,q);
  }
}


void LimpaListas(Cidade cid){
  cidade *c = (cidade*) cid;
  liberaLista(c->qua);
  liberaLista(c->hid);
  liberaLista(c->sem);
  liberaLista(c->tor);
}
Tree getTorresTree(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->tTor;
}

Quadra getQuadras(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->tQua;
}

Dicionario getDicionario(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->dici;
}

FILE *openArchPm(Cidade cid, char *patch, char *name){
  char *nomeCompleto;
  int sizePatch, sizeName;
  cidade *c = (cidade*) cid;
  sizePatch = 0;
  if(patch!=NULL)
    sizePatch = strlen(patch);
  sizeName = strlen(name);
  nomeCompleto = malloc(sizeof(char)*(sizePatch+sizeName+1));
  if(patch!=NULL)
    sprintf(nomeCompleto,"%s%s",patch,name);
  else
    sprintf(nomeCompleto,"%s",name);
  c->entPm = fopen(nomeCompleto,"r");
  free(nomeCompleto);
  if(c->entPm==NULL){
    printf("Erro na abertura do arquivo PM\n");
    return NULL;
  }
  else
    return c->entPm;
}

void closeArchPm(Cidade cid){
  cidade *c = (cidade*) cid;
  if(c->entPm!=NULL)
    fclose(c->entPm);
}

FILE *openArchEc(Cidade cid, char *patch, char *name){
  char *nomeCompleto;
  int sizePatch, sizeName;
  cidade *c = (cidade*) cid;
  sizePatch = 0;
  if(patch!=NULL)
    sizePatch = strlen(patch);
  sizeName = strlen(name);
  nomeCompleto = malloc(sizeof(char)*(sizePatch+sizeName+1));
  if(patch!=NULL)
    sprintf(nomeCompleto,"%s%s",patch,name);
  else
    sprintf(nomeCompleto,"%s",name);
  c->entEc = fopen(nomeCompleto,"r");
  free(nomeCompleto);
  if(c->entEc==NULL){
    printf("Erro na abertura do arquivo EC\n");
    return NULL;
  }
  else
    return c->entEc;
}

void openArchVia(char *patch, char *nome, Cidade cid){
  char *nomeCompleto;
  cidade *c = (cidade*) cid;

  if(patch!=NULL){
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+1));
    sprintf(nomeCompleto,"%s%s", patch, nome);
  }
  else{
    nomeCompleto = malloc(sizeof(char)*(strlen(nome)+1));
    sprintf(nomeCompleto,"%s", nome);
  }
  c->entVia = fopen(nomeCompleto,"r");
}

FILE *openArchTm(Cidade cid, char *patch, char *name){
  char *nomeCompleto;
  int sizePatch, sizeName;
  cidade *c = (cidade*) cid;
  sizePatch = 0;
  if(patch!=NULL)
    sizePatch = strlen(patch);
  sizeName = strlen(name);
  nomeCompleto = malloc(sizeof(char)*(sizePatch+sizeName+1));
  if(patch!=NULL)
    sprintf(nomeCompleto,"%s%s",patch,name);
  else
    sprintf(nomeCompleto,"%s",name);
  c->entTm = fopen(nomeCompleto,"r");
  free(nomeCompleto);
  if(c->entTm==NULL){
    printf("Erro na abertura do arquivo TM\n");
    return NULL;
  }
  else
    return c->entTm;
}

void closeArchEc(Cidade cid){
  cidade *c = (cidade*) cid;
  if(c->entEc!=NULL)
    fclose(c->entEc);
}

void closeArchTm(Cidade cid){
  cidade *c = (cidade*) cid;
  if(c->entTm!=NULL)
    fclose(c->entTm);
}

FILE *getArchPm(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->entPm;
}

FILE *getArchTm(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->entTm;
}

FILE *getArchEc(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->entEc;
}

void imprimePessoaSvg(Cidade cid, Pessoa p, FILE *arq){
  char *cep, *face;
  double x, y;
  Quadra qua;
  cidade *c;

  c = (cidade*) cid;
  if(p!=NULL){
    cep = pessoa_get_cep(p);
    face = pessoa_get_face(p);
    qua = NULL;
    if(cep !=NULL)
      qua = procuraQuadra(cid,cep);
    if(qua!=NULL&&cep!=NULL){
      if(strcmp(face,"N")==0){
        x = getQuadraX(qua) + pessoa_get_num(p);
        y = getQuadraY(qua) + getQuadraH(qua);
      }
      else if(strcmp(face,"S")==0){
        x = getQuadraX(qua) + pessoa_get_num(p);
        y = getQuadraY(qua);
      }
      else if(strcmp(face,"L")==0){
        x = getQuadraX(qua);
        y = getQuadraY(qua) + pessoa_get_num(p);
      }
      else if(strcmp(face,"O")==0){
        x = getQuadraX(qua) + getQuadraW(qua);
        y = getQuadraY(qua) + pessoa_get_num(p);
      }
      else{
        x = getQuadraX(qua);
        y = getQuadraY(qua);
      }
      /*fprintf(arq,"<circle cx=\"%f\" cy=\"%f\" r=\"8\" fill=\"blue\" ",x,y);
      fprintf(arq,"stroke=\"darkblue\" stroke-width=\"2\" fill-opacity=\"0.7\"/>\n");*/

      fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"20\" height=\"20\"", x, y);
      fprintf(arq," fill=\"#D9D919\" stroke=\"darkblue\" stroke-width=\"2\" fill-opacity=\"0.9\"/>\n");
      fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">M</text>\n", (x+5), (y+10));

    }
  }
}

void imprimeEstabelecimento(Cidade cid, Estab est, FILE *arq){
  char *cep, face;
  double x, y;
  Quadra qua;
  cidade *c;

  c = (cidade*) cid;
  if(est!=NULL){
    cep = estab_get_cep(est);
    face = estab_get_face(est);
    qua = NULL;
    if(cep !=NULL)
      qua = procuraQuadra(cid,cep);
    if(qua!=NULL&&cep!=NULL){
      switch(face){
        case 'N':
          x = getQuadraX(qua) + estab_get_num(est);
          y = getQuadraY(qua) + getQuadraH(qua);
          break;
        case 'S':
          x = getQuadraX(qua) + estab_get_num(est);
          y = getQuadraY(qua);
          break;
        case 'L':
          x = getQuadraX(qua);
          y = getQuadraY(qua) + estab_get_num(est);
          break;
        case 'O':
          x = getQuadraX(qua) + getQuadraW(qua);
          y = getQuadraY(qua) + estab_get_num(est);
          break;
        default:
          x = getQuadraX(qua);
          y = getQuadraY(qua);
          break;
      }
      /*fprintf(arq,"<circle cx=\"%f\" cy=\"%f\" r=\"8\" fill=\"blue\" ",x,y);
      fprintf(arq,"stroke=\"darkblue\" stroke-width=\"2\" fill-opacity=\"0.7\"/>\n");*/

      fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"20\" height=\"20\"", x, y);
      fprintf(arq," fill=\"#238E23\" stroke=\"#FF7F00\" stroke-width=\"2\" fill-opacity=\"0.9\"/>\n");
      fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">Est</text>\n", x, (y+10));

    }
  }
}

void imprimePessoasSvg(Cidade cid, FILE *arq){
  int i, size;
  Lista list;
  Posic aux;
  RegH reg;
  Pessoa pes;
  Hash h;
  cidade *c = (cidade*) cid;
  h = getHash(c->dici,"cpfXpessoa");
  size = hash_get_size(h);
  for(i=0;i<size;i++){
    list = hash_get_position(h,i);
    /*printf("\nTamanho da lista: %d\n", length(list));*/
    aux = getFirst(list);
    while(aux!=NULL){
      reg = get(list,aux);
      pes = hash_get_reg(reg);
      imprimePessoaSvg(cid,pes,c->saiSvg);
      aux = getNext(list,aux);
    }
  }
}


void imprimeEstabelecimentos(Cidade cid, FILE *arq){
  int i, size;
  Lista list;
  Posic aux;
  RegH reg;
  Estab est;
  Hash h;
  cidade *c = (cidade*) cid;
  h = getHash(c->dici,"codtestXest");
  size = hash_get_size(h);
  for(i=0;i<size;i++){
    list = hash_get_position(h,i);
    aux = getFirst(list);
    while(aux!=NULL){
      reg = get(list,aux);
      est = hash_get_reg(reg);
      imprimeEstabelecimento(cid,est,arq);
      aux = getNext(list,aux);
    }
  }
}

FILE *getArchVia(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->entVia;
}

void closeArchVia(Cidade cid){
  cidade *c = (cidade*) cid;
  if(c->entVia!=NULL)
    fclose(c->entVia);
}

void openArchSvgVia(char *patch, char *nome, char *sufixo, Cidade cid){
  char *nomeCompleto, *nome2;
  cidade *c = (cidade*) cid;
  nome2 = removeExtensao(nome);
  nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome2)+strlen(sufixo)+6));
  sprintf(nomeCompleto,"%s%s-%s.svg",patch,nome2,sufixo);
  c->saiSvgVias = fopen(nomeCompleto,"w");
}

FILE *getArchSvgVia(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->saiSvgVias;
}

void closeArchSvgVia(Cidade cid){
  cidade *c = (cidade*) cid;
  if(c->saiSvgVias!=NULL){
    fprintf(c->saiSvgVias,"</svg>\n");
    fclose(c->saiSvgVias);
  }
}

void cidade_cria_cruzamentos(Cidade cid, char *id, double x, double y){
  Vertice v;
  cidade *c = (cidade*) cid;

  v = grafo_create_vertice(id,x,y);
  grafo_insere_vertice(c->vias,v);
}

void cidade_cria_ruas(Cidade cid, char *nome, char *i,char *j,char *ldir, char *lesq, double cmp, double vm){
  Aresta a;
  Vertice v1, v2;
  cidade *c;
  c = (cidade*) cid;
  a = grafo_create_aresta(nome,ldir,lesq,cmp,vm);
  v1 = grafo_search_vertice_id(c->vias,i);
  v2 = grafo_search_vertice_id(c->vias,j);
  grafo_insere_aresta(c->vias,a,v1,v2);
}

Quadra cidade_busca_quadra(Cidade cid, char *cep){
  cidade *c;
  c = (cidade*) cid;
  return dicio_search_Quadra_cep(c->dici,cep);
}

Pessoa cidade_busca_pessoa_por_numcel(Cidade cid, char *numcel){
  cidade *c;
  Pessoa p;
  c = (cidade*) cid;
  p = dicio_searchPessoa_numcel(c->dici,numcel);
  return p;
}

Lista cidade_get_all_Torres(Cidade cid){
  cidade *c = (cidade*) cid;

  return c->tor;
}

double cidade_pega_ultima_torre_x(Cidade cid, Telefone t){
  char *id;
  Dicionario d;
  Lista list;
  d = getDicionario(cid);


}

Torre cidade_get_torre_mais_proxima(Cidade cid, double x, double y, char operadora){
  double x2, y2, dist, distMin;
  cidade *c;
  Lista list;
  Posic aux;
  Torre tor, torMin;
  distMin = INFINITO;
  c = (cidade*) cid;

  torMin = NULL;
  list = c->tor;
  aux = getFirst(list);
  while(aux!=NULL){
    tor = get(list,aux);
    if(getTorreOperadora(tor)==operadora){
      x2 = getTorreX(tor);
      y2 = getTorreY(tor);
      dist = distanceBetweenPoints(x,y,x2,y2);
      if(dist<distMin){
        torMin = tor;
        distMin = dist;
      }
    }
    aux = getNext(list,aux);

  }
  return torMin;
}

void cidade_remove_torre(Cidade cid, char *key){
  cidade *c = (cidade*) cid;
  dicio_remove_radio_numcel(c->dici, key);
}

void cidade_hash_insere_torre(Cidade cid, Torre tor, char *cel){
  cidade *c = (cidade*) cid;
  dicio_insere_radiobaseNumCel(c->dici,getTorreId(tor),cel);
}

Torre cidade_busca_torre_pelo_celular(Cidade cid, char *key){
  char *id, *idatual;
  cidade *c;
  Posic node;
  Torre tor;
  c = (cidade*) cid;
  id = dicio_searchRadio_numcel(c->dici,key);
  node = getFirst(c->tor);
  while(node!=NULL){
    tor = get(c->tor,node);
    idatual = getTorreId(tor);
    if(strcmp(id,idatual)==0)
      return tor;
    node = getNext(c->tor, node);
  }
  return NULL;
}

void cidade_imprime_caminho_svg(Cidade cid, Pilha vertices, char *color, FILE *arq){
  double x1, y1, x2, y2;
  cidade *c;
  Vertice v1, v2;
  c = (cidade*) cid;
  fprintf(arq,"<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
  imprimeQuadrasSvg(cid,arq);
  imprimeSemaforosSvg(cid,arq);
  imprimeHidrantesSvg(cid,arq);
  imprimeTorresSvg(cid,arq);
  imprimePessoasSvg(cid,arq);
  imprimeEstabelecimentos(cid,arq);
  if(getSizePilha(vertices)>0)
    v1 = pop(vertices);
  while(getSizePilha(vertices)>1){
    x1 = grafo_get_vertice_x(v1);
    y1 = grafo_get_vertice_y(v1);
    v2 = pop(vertices);
    x2 = grafo_get_vertice_x(v2);
    y2 = grafo_get_vertice_y(v2);
    fprintf(arq," <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" ", x1, y1, x2, y2);
    fprintf(arq,"stroke-width=\"2\" stroke=\"%s\"/>\n", color);
    v1 = v2;
  }
  if(getSizePilha(vertices)>0){
    v1 = pop(vertices);
    x1 = grafo_get_vertice_x(v1);
    y1 = grafo_get_vertice_y(v1);
    fprintf(arq," <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" ", x1, y1, x2, y2);
    fprintf(arq,"stroke-width=\"2\" stroke=\"%s\"/>\n", color);
  }
  fprintf(arq,"</svg>");
}

void cidade_imprime_caminho_escrito(Cidade cid, Pilha vertices, FILE *arq){
  char *dir, *nome1, *nome2;
  Vertice v1, v2, v3;
  Aresta a1, a2;
  if(getSizePilha(vertices)>2){
    v1 = pop(vertices);
    v2 = pop(vertices);
    while(getSizePilha(vertices)>0){
      v3 = pop(vertices);
      dir = grafo_calcula_quadrante(v1,v2);
      a1 = grafo_get_aresta_ligacao(NULL, v1, v2);
      a2 = grafo_get_aresta_ligacao(NULL, v2, v3);
      nome1 = grafo_get_aresta_nome(a1);
      nome2 = grafo_get_aresta_nome(a2);
      fprintf(arq,"Siga na direcao %s pela rua %s ate o cruzamento com a rua %s.\n", dir, nome1, nome2);
      v1 = v2;
      v2 = v3;
    }
  }
  else{
    fprintf(arq,"Caminho de consulta muito curto\n");
  }
}

/*void inserePessoa(Cidade cid, Pessoa p){
  cidade *c = (cidade*) cid;
  dicio_insere_pessoaCpf(c->dici,p);
  dicio_insere_pessoaNumCel(c->dici,p);
}

void inserePessoas(Cidade cid){
  Posic aux;
  cidade *c = (cidade*) cid;

  aux = getFirst(c->pes);
  while(aux!=NULL){
    inserePessoa(c,get(c->pes,aux));
    aux = getNext(c->pes,aux);
  }

}*/
/*void insereDescEstab(Cidade cid, char *type, char *desc){
  cidade *c = (cidade*) cid;
  dicio_insere_Desctype(c->dici,desc,type);
}*/

void insereQuadrasHash(Cidade cid){
  cidade *c = (cidade*) cid;
  Posic aux;
  Quadra qua;
  aux = getFirst(c->qua);
  while(aux!=NULL){
    qua = get(c->qua,aux);
    dicio_insere_quadraCep(c->dici,qua);
    aux = getNext(c->qua,aux);
  }
}

Pessoa cidade_busca_pessoa_por_cpf(Cidade cid, char *key){
  cidade *c;
  c = (cidade*) cid;
  return dicio_searchPessoa_cpf(c->dici,key);
}

Grafo cidade_get_grafo(Cidade cid){
  cidade *c = (cidade*) cid;
  return c->vias;
}

Posic cidade_busca_equipe_urb(Cidade cid, char *id, char *tipo){
  char *idaux;
  cidade *c = (cidade*) cid;
  Posic node, algo;

  *tipo = 'a';
  node = getFirst(c->hid);
  while(node!=NULL){
    algo = get(c->hid,node);
    idaux = getHidranteId(algo);
    if(strcmp(idaux,id)==0){
      *tipo = 'h';
      return algo;
    }
    node = getNext(c->hid,node);
  }

  node = getFirst(c->sem);
  while(node!=NULL){
    algo = get(c->hid,node);
    idaux = getSemaforoId(algo);
    if(strcmp(idaux,id)==0){
      *tipo = 's';
      return algo;
    }
    node = getNext(c->sem,node);
  }

}

Estab cidade_busca_estab_proximo(Cidade cid, double x, double y){
  int i, size, num;
  double distMin, dist, x2, y2;
  char *cep, face, face2[2];
  cidade *c;
  Lista list;
  Hash h;
  Posic node;
  Estab est, estMin;
  Quadra qua;
  estMin = NULL;
  c = (cidade*) cid;
  h = getHash(c->dici, "codtestXest");
  size = hash_get_size(h);
  distMin = INFINITO;
  for(i=0;i<size;i++){
    list = hash_get_position(h,i);
    node = getFirst(list);
    while(node!=NULL){
      est = get(list,node);
      cep = estab_get_cep(est);
      face = estab_get_face(est);
      face2[0] = face;
      face2[1] = '\0';
      num = estab_get_num(est);
      qua = cidade_busca_quadra(cid,cep);
      x2 = calcula_quadra_ponto_x(qua,face2,num);
      y2 = calcula_quadra_ponto_y(qua,face2,num);
      dist = distanceBetweenPoints(x,y,x2,y2);
      if(dist<distMin){
        distMin = dist;
        estMin = est;
      }
    }
  }
  return estMin;
}
