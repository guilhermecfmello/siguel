#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Procedimentos.h"
#include "Lista.h"
#include "Escrita.h"
#include "Operacoes.h"


Cidade processoGeo(char *nomeGeo, char *dirSaida, char *nomeEntradaQry, Formas *formaGeral, Cidade cid){
  int id, id2, cond, cond1, cond2;
  double x, y, raio, alt, larg, x2, y2;
  double larg1, larg2, alt1, alt2, vazao, tempo;
  char *nomeSuf, *auxFree, *auxGeo;
  char cor[20], auxSuf[30], auxCor[20], cep[40];
  char op, typeF1, typeF2;
  void* aux;
  FILE *saiSvgSuf, *ent, *saiTxtCons;
  Forma f1, f2;
  Rect ret = NULL;
  Circle circ = NULL;
  Quadra qua = NULL;
  Hidrante hid = NULL;
  Semaforo sem = NULL;
  Torre tor = NULL;
  Formas f = createFormas();
  ent = getArchGeo(cid);
  saiTxtCons = getArchTxtCons(cid);
  while(!feof(ent)){
    fscanf(ent,"%c", &op);
    switch(op){
      case 'c':
        fscanf(ent,"%c", &op);
        switch(op){
          case 'q':
            fscanf(ent," %s %s", cor, auxCor);
            setCoresQuadras(cid, cor, auxCor);
            break;
          case 'h':
            fscanf(ent," %s %s", cor, auxCor);
            setCoresHidrantes(cid, cor, auxCor);
            break;
          case 't':
            fscanf(ent," %s %s", cor, auxCor);
            setCoresTorres(cid, cor, auxCor);
            break;
          case 's':
            fscanf(ent," %s %s", cor, auxCor);
            setCoresSemaforos(cid, cor, auxCor);
            break;
          case ' ':
            fscanf(ent,"%d %lf %lf %lf %s", &id,&raio,&x,&y,cor);
            circ = createCircle(id,raio,x,y,cor);
            insereCirculo(f,circ);
            break;
        }
        break;
      case 'r':
        fscanf(ent," %d %lf %lf %lf %lf %s", &id,&larg,&alt,&x,&y,cor);
        ret = createRectangle(id,larg,alt,x,y,cor);
        insereRetangulo(f, ret);
        break;
      case 'o':
        fscanf(ent," %d  %d ", &id, &id2);
        cond1 = procuraFigura(&f1,&typeF1, f, id);
        cond2 = procuraFigura(&f2,&typeF2, f, id2);
        if(cond1 && cond2){
          moduloO(&x,&y,&larg,&alt,&cond,typeF1,typeF2,f1,f2);
          fprintf(saiTxtCons,"Sobreposicao %d %d\n", id, id2);
          if(cond){
            ret = createRectangle(0,larg,alt,x,y,"none");
            insereSob(f,ret);
            fprintf(saiTxtCons, "  As figuras se sobrepoem\n");
          }
          else fprintf(saiTxtCons, "  As figuras nao se sobrepoem\n");
        }
        break;
      case 'i':
        fscanf(ent," %d %lf %lf ", &id, &x, &y);
        cond = procuraFigura(&f1, &typeF1, f, id);
        fprintf(saiTxtCons, "Ponto interno: %d %f %f\n", id, x, y);
        if(cond){
          if(typeF1=='c') cond = verPointCircInt(f1,x,y);
          else cond = verPointRectInt(f1,x,y);
        }
        if(cond) fprintf(saiTxtCons,"  O ponto eh interno a figura\n");
        else fprintf(saiTxtCons, "  O ponto nao eh interno a figura\n");
        break;
      case 'd':
        fscanf(ent," %d %d ", &id, &id2);
        cond1 = procuraFigura(&f1,&typeF1,f,id);
        cond2 = procuraFigura(&f2,&typeF2,f,id2);
        x = getCentroX(f1,typeF1);
        y = getCentroY(f1,typeF1);
        x2 = getCentroX(f2,typeF2);
        y2 = getCentroY(f2,typeF2);
        raio = distanceBetweenPoints(x,y,x2,y2);
        if (cond1&&cond2) fprintf(saiTxtCons,"Distancia entre centros de massa: %d %d\n  %f\n", id, id2, raio);
        else fprintf(saiTxtCons, "Erro, Id's invalidos\n");
        break;
      case 'a':
        fscanf(ent," %s %s",auxSuf,auxCor);
        nomeSuf = malloc(sizeof(char)*(strlen(auxSuf)+strlen(nomeGeo)+strlen(dirSaida)+6));
        sprintf(nomeSuf,"%s%s-%s.svg",dirSaida, nomeGeo, auxSuf);
        saiSvgSuf = fopen(nomeSuf,"w");
        fprintf(saiSvgSuf,"<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
        imprimeRetangulosSuf(saiSvgSuf,f,auxCor);
        imprimeCirculosSuf(saiSvgSuf,f,auxCor);
        fprintf(saiSvgSuf,"</svg>\n");
        fclose(saiSvgSuf);
        break;
      case 'q':
        fscanf(ent," %lf %lf %lf %lf %s", &x, &y, &larg, &alt, cep);
        qua = createQuadra(x,y,larg,alt,cep);
        insereQuadra(cid, qua);
        break;
      case 'h':
        fscanf(ent,"%c",&op);
        if(op=='I'){
          fscanf(ent," %s %lf",cep , &vazao);
          hid = procuraHidrante(cid, cep);
          setHidranteVazao(hid,vazao);
        }
        else{
          fscanf(ent,"%lf %lf %s", &x, &y, cep);
          hid = createHidrante(x,y,cep);
          insereHidrante(cid, hid);
        }
        break;
      case 's':
        fscanf(ent,"%c", &op);
        if(op=='I'){
          fscanf(ent," %s %lf", cep, &tempo);
          sem = procuraSemaforo(cid,cep);
          setSemaforoTempo(sem,tempo);
        }
        else{
          fscanf(ent,"%lf %lf %s", &x, &y, cep);
          sem = createSemaforo(x,y,cep);
          insereSemaforo(cid, sem);
        }
        break;
      case 't':
        fscanf(ent,"%c",&op);
        if(op=='I'){
          fscanf(ent," %s %lf",cep, &raio);
          tor = procuraTorre(cid, cep);
          setTorreRaio(tor, raio);
        }
        else{
          fscanf(ent,"%lf %lf %s", &x, &y, cep);
          tor = createTorre(x,y,cep);
          insereTorre(cid, tor);
        }
        break;
      case '#':
        id = getNumQuadras(cid);
        if(nomeEntradaQry!=NULL)fprintf(getArchTxtComp(cid),"Arquivo Geo:%s |Arquivo Qry:%s %d %d ",nomeGeo,nomeEntradaQry, id, 0);
        else fprintf(getArchTxtComp(cid),"%s.geo %d %d ",nomeGeo,id, 0);
        break;
    }
  }
  *formaGeral = f;
  return (Cidade)cid;
}

Cidade processoQry(Cidade c){
  double x, y, larg, alt, raio;
  int numQuaRem, numComps;
  char *nomeSvg, *nomeTxt, *auxNome;
  char end[40];
  char op, op2, op3;
  Forma f1, f2, f3;
  RecursiveSearchPtrRet ptrFuncRet;
  RecursiveSearchPtrCirc ptrFuncCirc;
  FILE *entQry, *saiTxt, *saiTxt2;
  entQry = getArchQry(c);
  saiTxt = getArchTxtComp(c);
  saiTxt2 = getArchTxtCons(c);
  numQuaRem = 0;
  numComps = 0;
  if(entQry!=NULL){
    while(!feof(entQry)){
      fscanf(entQry,"%c", &op);
      switch(op){
        case 'd':
                  fscanf(entQry,"%c ", &op);
                  fscanf(entQry,"%lf %lf %lf %lf", &x, &y, &larg, &alt);
                  f1 = createRectangle(0,larg,alt,x,y,"blue");

                  switch(op){
                        case 'q':
                          f2 = getQuadraRet(c,f1);
                          while(f2!=NULL){
                            numQuaRem++;
                            removeQuadra(c,f2);
                            f2 = getQuadraRet(c,f1);
                          }
                          break;
                        case 'h':
                          f2 = getHidranteRet(c,f1);
                          while(f2!=NULL){
                            removeHidrante(c,f2);
                            f2 = getHidranteRet(c,f1);
                          }
                          break;
                        case 's':
                          f2 = getSemaforoRet(c,f1);
                          while(f2!=NULL){
                            removeSemaforo(c,f2);
                            f2 = getSemaforoRet(c,f1);
                          }
                          break;
                        case 't':
                          f2 = getTorreRet(c,f1);
                          while(f2!=NULL){
                            removeTorre(c,f2);
                            f2 = getTorreRet(c,f1);
                          }
                          break;
                  }
          break;
        case 'D':
                fscanf(entQry,"%c ", &op);
                fscanf(entQry,"%lf %lf %lf", &x, &y, &raio);
                f1 = createCircle(0,raio,x,y,"blue");
                fprintf(getArchSvg(c)," <circle cx=\"%f\" cy=\"%f\" r=\"%f\"",x,y,raio);
                fprintf(getArchSvg(c)," fill=\"red\" stroke=\"black\"/>\n");
                switch(op){
                  case 'q':
                    f2 = getQuadraCirc(c,f1);
                    while(f2!=NULL){
                      numQuaRem++;
                      removeQuadra(c,f2);
                      f2 = getQuadraCirc(c,f1);
                    }
                    break;
                  case 'h':
                    f2 = getHidranteCirc(c,f1);
                    while(f2!=NULL){
                      removeHidrante(c,f2);
                      f2 = getHidranteCirc(c,f1);
                    }
                    break;
                  case 's':
                    f2 = getSemaforoCirc(c,f1);
                    while(f2!=NULL){
                      removeSemaforo(c,f2);
                      f2 = getSemaforoCirc(c,f1);
                    }
                    break;
                  case 't':
                    f2 = getTorreCirc(c,f1);
                    while(f2!=NULL){
                      removeTorre(c,f2);
                      f2 = getTorreCirc(c,f1);
                    }
                    break;
                }
          break;
        case 'c':
          fscanf(entQry,"%c%c%c",&op, &op2, &op3);
          if(op=='r'&&op2=='d'&&op3=='?'){
            fscanf(entQry," %s ", end);
            f1 = procuraElemento(c,end,&op);
            if(f1!=NULL){
              switch(op){
                case 'q':
                  x = getQuadraX(f1);
                  y = getQuadraY(f1);
                  fprintf(saiTxt2,"CEP/ID: %s tipo: Quadra\n X= %f Y=%f\n", end, x, y);
                  break;
                case 'h':
                  x = getHidranteX(f1);
                  y = getHidranteY(f1);
                  fprintf(saiTxt2,"CEP/ID: %s tipo: Hidrante\n X= %f Y= %f\n", end, x, y);
                  break;
                case 's':
                  x = getSemaforoX(f1);
                  y = getSemaforoY(f1);
                  fprintf(saiTxt2,"CEP/ID: %s tipo: Semaforo\n X= %f Y= %f\n", end, x, y);
                  break;
                case 't':
                  x = getTorreX(f1);
                  y = getTorreY(f1);
                  fprintf(saiTxt2,"CEP/ID: %s tipo: Torre\n X= %f Y= %f\n", end, x, y);
                  break;
              }
            }
          }
          break;

      }


    }
    }
  fprintf(saiTxt," %d %d\n", numQuaRem, numComps);
  return c;
}
