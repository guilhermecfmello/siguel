#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Operacoes.h"
#include "Cidade.h"
#include "Escrita.h"
#include "Formas.h"
#include "Procedimentos.h"
#include "ConvexHull.h"

static int numQuaRem, numCompsRem, numQuaIns, numCompsIns;

int main(int argc,char *argv[]){
  int num, size;
  char *nomeEntradaGeo, *dirSaida, *dirEntrada;
  char *aux, *entradaPadrao, *nomeEntradaQry, *nomeBaseQry;
  char *nomePm, *nomeEc, *nomeTm, *nomeVia;
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
  nomePm = pegaParametro(argc,argv,"-pm");
  nomeTm = pegaParametro(argc,argv,"-tm");
  nomeEc = pegaParametro(argc,argv,"-ec");
  nomeVia = pegaParametro(argc,argv,"-v");
  acc = parametroAcc(argc, argv);
  cid = createCidade();
  if(parametroId(argc,argv))
    printf("\nAluno Guilherme Mello\n");

  /*CRIACAO DOS NOMES PARA ABERTURA DE ARQUIVOS*/
  entradaPadrao = removeExtensao(nomeEntradaGeo);
  entradaPadrao = filtraNome(entradaPadrao);
  dirSaida = colocaBarra(dirSaida);
  dirEntrada = colocaBarra(dirEntrada);

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
  if(nomeEc!=NULL)
    openArchEc(cid,dirEntrada,nomeEc);
  if(nomePm!=NULL)
    openArchPm(cid,dirEntrada,nomePm);
  if(nomeTm!=NULL)
    openArchTm(cid,dirEntrada,nomeTm);
  if(nomeVia!=NULL)
    openArchVia(dirEntrada,nomeVia,cid);

  if(acc) openArchTxtComp(dirSaida,"resumo","a",cid);
  else openArchTxtComp(dirSaida,"resumo","w",cid);

  /*TRATAMENTO DOS ARQUIVOS DE ENTRADA DA CIDADE*/
  cid = processoGeo(entradaPadrao,dirSaida,nomeBaseQry, &f, cid);
  /*MUDANCA DA ESTRUTURA DE DADOS DOS ELEMENTOS DA CIDADE
  PASSANDO DE LISTA PARA QUADTREE BALANCEADA PELO CONVEXHULL*/
  listToQuadTreeCH(cid);
  insereQuadrasHash(cid);
  if(nomeEc!=NULL)
    cid = processoEc(cid);
  if(nomePm!=NULL)
    cid = processoPm(cid);
  if(nomeTm!=NULL)
    cid = processoTm(cid);
  if(nomeVia!=NULL);
    cid = processoVia(cid);
  cid = processoQry(cid, entradaPadrao,nomeEntradaQry , dirSaida);
  /*LimpaListas(cid);*/
  /*IMPRESSAO DA CIDADE NO ARQUIVO QRY*/
  saiSvg = getArchSvg(cid);
  imprimeCirculos(saiSvg, f);
  imprimeRetangulos(saiSvg, f);
  imprimeRetangulosSob(saiSvg, f);
  imprimeQuadrasSvg(cid,saiSvg);
  imprimeSemaforosSvg(cid,saiSvg);
  imprimeHidrantesSvg(cid,saiSvg);
  imprimeTorresSvg(cid,saiSvg);
  imprimePessoasSvg(cid,saiSvg);
  imprimeEstabelecimentos(cid,saiSvg);
  saiSvg = NULL;

  /*FECHAMENTO DOS ARQUIVOS DA CIDADE*/
  closeArchSvg(cid);
  closeArchQry(cid);
  closeArchGeo(cid);
  closeArchTxtCons(cid);
  closeArchTxtComp(cid);
  closeArchPm(cid);
  closeArchTm(cid);
  closeArchEc(cid);



  return 0;
}
