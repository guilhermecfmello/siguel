#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
/*INCLUINDO DADOS PARA O SEGUNDO COMMIT*/
typedef struct _cidade{
  Lista qua;
  Lista hid;
  Lista sem;
  Lista tor;
  FILE *saiSvg;/*ARQUIVO DE SAIDA EM FORMATO SVG, CONTEM O MAPA DA CIDADE*/
  FILE *saiTxtConsultas;/*ARQUIVO DE SAIDA TXT, DESCRICAO DAS CONSULTAS FEITAS*/
  FILE *saiTxtComp;/*ARQUIVO DE SAIDA TXT, O NUMERO DE COMPARACOES PARA INSERCAO/REMOCAO DA LISTA*/
  FILE *entGeo;/*ARQUIVO DE ENTRADA, ARQUIVO .GEO QUE CONTEM OS ELEMENTOS DA CIDADE.*/
  FILE *entQry;/*ARQUIVO DE ENTRADA, ARQUIVO .QRY QUE CONTEM INSTRUCOES DE EXCLUSAO DE ITENS*/
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
  c->saiSvg = NULL;
  c->saiTxtConsultas = NULL;
  c->saiTxtComp = NULL;
  c->entGeo = NULL;
  c->entQry = NULL;
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

void imprimeQuadrasSvg(Cidade c){
    double x, y, w, h;
    char *cep;
    FILE *arq;
    cidade *cid = (cidade*) c;
    Posic aux, content;
    arq = getArchSvg(c);
    aux = getFirst(cid->qua);
    while(aux!=NULL){
      content = get(cid->qua,aux);
      x = getQuadraX(content);
      y = getQuadraY(content);
      w = getQuadraW(content);
      h = getQuadraH(content);
      cep = getQuadraCep(content);
      fprintf(arq," <rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\"", x, y, w, h);
      fprintf(arq," fill=\"%s\" stroke=\"%s\" stroke-width=\"2\"/>\n", cid->cfillQuadras, cid->cstrkQuadras);
      x += 6;
      y += 25;
      /*fprintf(arq," <text x=\"%f\" y=\"%f\" fill=\"black\">", x, y);
      fprintf(arq,"%s</text>\n", cep);*/
      aux = getNext(cid->qua,aux);
    }
}

void imprimeHidrantesSvg(Cidade c){
  double x, y;
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
  }
}

void imprimeSemaforosSvg(Cidade c){
  int i;
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
  }
}

void imprimeTorresSvg(Cidade c){
  double x, y;
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
  }
}



int getNumQuadras(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->numQuadras;
}

Quadra getQuadraRet(Cidade c, Rect r, int *comp){
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

Hidrante getHidranteRet(Cidade c, Rect r){
  double x, y;
  cidade *cid = (cidade*) c;
  Hidrante h;
  Posic node = getFirst(cid->hid);
  while(node!=NULL){
    h = get(cid->hid,node);
    x = getHidranteX(h);
    y = getHidranteY(h);
    if(verPointRectInt(r,x,y)) return node;
    node = getNext(cid->hid,node);
  }
  return NULL;
}

Hidrante getHidranteCirc(Cidade c, Circle circ){
  double x, y;
  cidade *cid = (cidade*) c;
  Hidrante h;
  Posic node = getFirst(cid->hid);
  while(node!=NULL){
    h = get(cid->hid,node);
    x = getHidranteX(h);
    y = getHidranteY(h);
    if(verPointCircInt(circ,x,y)) return node;
    node = getNext(cid->hid,node);
  }
  return NULL;
}

Semaforo getSemaforoRet(Cidade c, Rect r){
  double x, y;
  cidade *cid = (cidade*) c;
  Semaforo s;
  Posic node = getFirst(cid->sem);
  while(node!=NULL){
    s = get(cid->sem,node);
    x = getSemaforoX(s);
    y = getSemaforoY(s);
    if(verPointRectInt(r,x,y)) return node;
    node = getNext(cid->sem,node);
  }
  return NULL;
}

Semaforo getSemaforoCirc(Cidade c, Circle circ){
  double x, y;
  cidade *cid = (cidade*) c;
  Semaforo s;
  Posic node = getFirst(cid->sem);
  while(node!=NULL){
    s = get(cid->sem,node);
    x = getSemaforoX(s);
    y = getSemaforoY(s);
    if(verPointCircInt(circ,x,y)) return node;
    node = getNext(cid->sem,node);
  }
  return NULL;
}

Torre getTorreRet(Cidade c, Rect r){
  double x, y;
  cidade *cid = (cidade*) c;
  Torre t;
  Posic node = getFirst(cid->tor);
  while(node!=NULL){
    t = get(cid->tor,node);
    x = getTorreX(t);
    y = getTorreY(t);
    if(verPointRectInt(r,x,y)) return node;
    node = getNext(cid->tor,node);
  }
  return NULL;
}

Torre getTorreCirc(Cidade c, Circle circ){
  double x, y;
  cidade *cid = (cidade*) c;
  Torre t;
  Posic node = getFirst(cid->tor);
  while(node!=NULL){
    t = get(cid->tor,node);
    x = getSemaforoX(t);
    y = getSemaforoY(t);
    if(verPointCircInt(circ,x,y)) return node;
    node = getNext(cid->tor,node);
  }
  return NULL;
}

void removeQuadra(Cidade c, Quadra q){
  cidade *cid = (cidade*) c;
  remover(cid->qua,q);
}

void removeHidrante(Cidade c, Hidrante h){
  cidade *cid = (cidade*) c;
  remover(cid->hid,h);
}

void removeSemaforo(Cidade c, Semaforo s){
  cidade *cid = (cidade*) c;
  remover(cid->sem,s);
}

void removeTorre(Cidade c, Torre t){
  cidade *cid = (cidade*) c;
  remover(cid->tor,t);
}

Quadra procuraQuadra(Cidade c, char *end){
  char *cep;
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
  return NULL;
}

Hidrante procuraHidrante(Cidade c, char *end){
  char *id;
  cidade *cid = (cidade*) c;
  Posic node;
  Quadra aux;
  node = getFirst(cid->hid);
  while(node!=NULL){
    aux = get(cid->hid,node);
    id = getHidranteId(aux);
    if(strcmp(id,end)==0) return aux;
    node = getNext(cid->hid, node);
  }
  return NULL;
}

Semaforo procuraSemaforo(Cidade c, char *end){
  char *id;
  cidade *cid = (cidade*) c;
  Posic node;
  Quadra aux;
  node = getFirst(cid->sem);
  while(node!=NULL){
    aux = get(cid->sem, node);
    id = getSemaforoId(aux);
    if(strcmp(id,end)==0) return aux;
    node = getNext(cid->sem, node);
  }
  return NULL;
}

Torre procuraTorre(Cidade c, char *end){
  char *id;
  cidade *cid = (cidade*) c;
  Posic node;
  Quadra aux;
  node = getFirst(cid->tor);
  while(node!=NULL){
    aux = get(cid->tor,node);
    id = getTorreId(aux);
    if(strcmp(id,end)==0) return aux;
    node = getNext(cid->tor, node);
  }
  return NULL;
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
  printf("Nome Completo - openArchSvg: %s",  nomeCompleto);
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
  printf("\nPatch: %s |Nome: %s\n", patch, nome);
  if(patch!=NULL){
    nomeCompleto = malloc(sizeof(char)*(strlen(patch)+strlen(nome)+5));
    sprintf(nomeCompleto,"%s%s",patch,nome);
  }
  else{
    nomeCompleto = malloc(sizeof(char)*(strlen(nome)+5));
    sprintf(nomeCompleto,"%s",nome);
  }
  printf("nomeCompleto no openArchGeo: %s", nomeCompleto);
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

FILE *getArchSvg(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->saiSvg;
}

Quadra getQuadras(Cidade c){
  cidade *cid = (cidade*) c;
  return cid->qua;
}
