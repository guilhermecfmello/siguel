#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Operacoes.h"
#include "Cidade.h"
#include "Escrita.h"
#include "Formas.h"
#include "Procedimentos.h"
#include "ConvexHull.h"

int main(int argc,char *argv[]){
  int num, size;
  char *nomeEntradaGeo, *dirSaida, *dirEntrada;
  char *aux, *entradaPadrao, *nomeEntradaQry, *nomeBaseQry;
  int acc;
  Quadra q;
  getX gx;
  getY gy;
  vectorNode *vectorTest;
  Cidade cid;
  FILE *saiSvg;
  Formas f;
  Pilha ch;

  nomeEntradaGeo = pegaParametro(argc,argv,"-f");/*Obrigatorio*/
  dirSaida = pegaParametro(argc,argv,"-o"); /*Obrigatorio*/
  dirEntrada = pegaParametro(argc,argv,"-e");
  nomeEntradaQry = pegaParametro(argc,argv,"-q");
  acc = parametroAcc(argc, argv);
  cid = createCidade();

  /*CRIACAO DOS NOMES PARA ABERTURA DE ARQUIVOS*/
  entradaPadrao = removeExtensao(nomeEntradaGeo);
  entradaPadrao = filtraNome(entradaPadrao);
  dirSaida = colocaBarra(dirSaida);
  dirEntrada = colocaBarra(dirEntrada);
  printf("\nEntradaPadrao: %s\n", entradaPadrao);

  /*printf(">>dirEntrada na main: %s", dirEntrada);*/
  if(nomeEntradaQry!=NULL){
    aux = filtraNome(nomeEntradaQry);
    nomeBaseQry = removeExtensao(aux);
  }
  else nomeBaseQry = NULL;

  /*ABERTURA DE ARQUIVOS*/
  openArchSvg(dirSaida,entradaPadrao,nomeBaseQry, cid);
  openArchTxtCons(dirSaida,entradaPadrao,nomeBaseQry,cid);
  openArchGeo(dirEntrada,nomeEntradaGeo,cid);
  openArchQry(dirEntrada,nomeEntradaQry,cid);
  if(acc) openArchTxtComp(dirSaida,"resumo","a",cid);
  else openArchTxtComp(dirSaida,"resumo","w",cid);

  /*TRATAMENTO DOS ARQUIVOS DE ENTRADA DA CIDADE*/
  cid = processoGeo(entradaPadrao,dirSaida,nomeBaseQry, &f, cid);
  cid = processoQry(cid);

  /*IMPRESSAO DA CIDADE NO ARQUIVO QRY*/
  saiSvg = getArchSvg(cid);
  imprimeCirculos(saiSvg, f);
  imprimeRetangulos(saiSvg, f);
  imprimeRetangulosSob(saiSvg, f);
  saiSvg = NULL;
  imprimeQuadrasSvg(cid);
  imprimeSemaforosSvg(cid);
  imprimeHidrantesSvg(cid);
  imprimeTorresSvg(cid);

  gx = &getQuadraX;
  gy = &getQuadraY;
  q = getQuadras(cid);
  ch = convexHull(q, gx, gy);

  /*FECHAMENTO DOS ARQUIVOS DA CIDADE*/
  closeArchSvg(cid);
  closeArchQry(cid);
  closeArchGeo(cid);
  closeArchTxtCons(cid);
  closeArchTxtComp(cid);



  return 0;
}
