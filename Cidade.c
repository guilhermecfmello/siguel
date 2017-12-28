#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
#include "Escrita.h"

typedef struct _cidade{
  Lista qua;
  Lista hid;
  Lista sem;
  Lista tor;
  Tree tQua;/*Quadtree com os elementos da cidade*/
  Tree tHid;/*Quadtree com os elementos da cidade*/
  Tree tSem;/*Quadtree com os elementos da cidade*/
  Tree tTor;/*Quadtree com os elementos da cidade*/
  FILE *saiSvg;/*ARQUIVO DE SAIDA EM FORMATO SVG, CONTEM O MAPA DA CIDADE*/
  FILE *saiTxtConsultas;/*ARQUIVO DE SAIDA TXT, DESCRICAO DAS CONSULTAS FEITAS*/
  FILE *saiTxtComp;/*ARQUIVO DE SAIDA TXT, O NUMERO DE COMPARACOES PARA INSERCAO/REMOCAO DA LISTA*/
  FILE *entGeo;/*ARQUIVO DE ENTRADA, ARQUIVO .GEO QUE CONTEM OS ELEMENTOS DA CIDADE.*/
  FILE *entQry;/*ARQUIVO DE ENTRADA, ARQUIVO .QRY QUE CONTEM INSTRUCOES DE EXCLUSAO DE ITENS*/
  FILE *areaTorres;/*ARQUIVO DE SAIDA, SVG QUE MOSTRA A CIDADE, A AREA DE COBERTURA DAS TORRES E SEU ENVOLTORIO CONVEXO*/
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
  c->saiSvg = NULL;
  c->saiTxtConsultas = NULL;
  c->saiTxtComp = NULL;
  c->entGeo = NULL;
  c->entQry = NULL;
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
      printf("\npatch: %s nome: %s nomeQry: %s sufixo: %s", patch, nome, nomeQry, sufixo);
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
