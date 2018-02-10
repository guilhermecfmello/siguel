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
  Dicionario dici;
  Formas f = createFormas();
  Rect ret = NULL;
  Circle circ = NULL;
  Quadra qua = NULL;
  Hidrante hid = NULL;
  Semaforo sem = NULL;
  Torre tor = NULL;
  dici = getDicionario(cid);
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
        else if(op=='u'){
          fscanf(ent,"%s ", cep);
          tor = procuraTorreList(cid,cep);
          dicio_insere_torre_sercomtuel(dici,tor);
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
          tor = procuraTorreList(cid, cep);
          setTorreRaio(tor, raio);
        }
        else{
          fscanf(ent,"%lf %lf %s", &x, &y, cep);
          tor = createTorre(x,y,cep);
          insereTorre(cid, tor);
        }
        break;
      case '#':
        break;
      case 'u':
        fscanf(ent,"%c ",&op);
        if(op=='m'){
          fscanf(ent,"%s ", cep);
          tor = procuraTorreList(cid,cep);
          dicio_insere_torre_uelmobile(dici,tor);
        }
        break;
    }
  }
  *formaGeral = f;
  return (Cidade)cid;
}

Cidade processoQry(Cidade c, char *nomeBase, char *nomeQry, char *dirBSD){
  double x, y, larg, alt, raio;
  int numQuaRem, compsIns, compsRem, id;
  char *nomeSvg, *nomeTxt, *auxNome, *busca;
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
          case 'p':
            fscanf(entQry,"%c%c ",&op,&op2);
            if(op=='c'&&op2=='?'){
              fscanf(entQry,"%s%c", end,&op);
              if(op==' '){
                fscanf(entQry,"%lf %lf %lf %lf",&x,&y,&larg,&alt);
                f1 = createRectangle(0,larg,alt,x,y,"blue");
                coberturaTorres(c,f1,nomeBase,nomeQry,dirBSD,end);
                free(f1);
              }
              else
                coberturaTorres(c,NULL,nomeBase,nomeQry,dirBSD,end);
            }
            break;
            case 'a':
            fscanf(entQry,"%c%c ",&op,&op2);
            if(op=='c'&&op2=='?'){
              fscanf(entQry,"%s%c", end,&op);
              if(op==' '){
                fscanf(entQry,"%lf %lf %lf %lf", &x, &y, &larg, &alt);
                f1 = createRectangle(0,larg,alt,x,y,"red");
                coberturaTorresTxt(c,f1);
                free(f1);
              }
              else
                coberturaTorresTxt(c,NULL);
            }
      }


    }
    id = getNumQuadras(c);
    compsIns = getCompsIns(getQuadras(c));
    compsRem = getCompsRem(getQuadras(c));
    /*SE HOUVE ENTRADA DE ARQUIVOS QRY*/
    if(nomeQry!=NULL){
      fprintf(saiTxt,"Arquivo Geo:%s |Arquivo Qry:%s %d %d ",nomeBase,nomeQry, id, compsIns);
      fprintf(saiTxt," %d %d\n", numQuaRem, getCompsRem(getQuadras(c)));
    }
    else{
      fprintf(saiTxt,"%s.geo %d %d ",nomeBase,id, 0);
      fprintf(saiTxt," %d %d\n", numQuaRem, getCompsRem(getQuadras(c)));
    }
    /*SE NAO HOUVE O PROCESSAMENTO DE UM ARQUIVO QRY*/
    }
    id = getNumQuadras(c);
    if(nomeQry!=NULL){
      fprintf(saiTxt,"Arquivo Geo:%s |Arquivo Qry:%s %d %d ",nomeBase,nomeQry, id, compsIns);
      fprintf(saiTxt," 0 0\n");
    }
    else{
      fprintf(saiTxt,"%s.geo %d %d ",nomeBase,id, 0);
      fprintf(saiTxt," 0 0\n");
    }
    return c;
}

Cidade processoPm(Cidade cid){
  int num;
  char cpf[20], nome[60], sobrenome[60], sexo, nasc[11];
  char cep[20], face[10], comp[30];
  char op;
  FILE *arq;
  RegH aux;
  Pessoa pes;
  Dicionario dici;
  dici = getDicionario(cid);
  arq = getArchPm(cid);
  while(!feof(arq)){
    fscanf(arq,"%c ", &op);
    switch(op){
      case 'p':
        fscanf(arq,"%s %s %s %c %s ",cpf,nome,sobrenome,&sexo,nasc);
        pes = pessoa_create(cpf,nome,sobrenome,sexo,nasc);
        dicio_insere_pessoaCpf(dici,pes);
        break;
      case 'm':
        fscanf(arq,"%s %s %s %d %s ", cpf, cep, face,&num,comp);
        pes = dicio_searchPessoa_cpf(dici,cpf);
        /*printf("\nnum: %d", pessoa_get_num(pes));*/
        pessoa_set_num(pes, num);
        pessoa_set_comp(pes, comp);
        pessoa_set_cep(pes, cep);
        pessoa_set_face(pes, face);
        break;
      default:
        printf("Erro no comando do arquivo PM\n");
        break;
    }
  }
  return cid;
}

Cidade processoTm(Cidade cid){
  char op[10], cpf[20], numcel[20];
  Dicionario dici;
  Pessoa pes;
  Telefone tel;
  FILE *arq;
  dici = getDicionario(cid);
  arq = getArchTm(cid);
  while(!feof(arq)){
    fscanf(arq,"%s ",op);
    fscanf(arq,"%s %s", cpf, numcel);
    pes = dicio_searchPessoa_cpf(dici, cpf);
    tel = telefone_create(numcel,NULL);
    if(pes!=NULL){
      pessoa_set_tel(pes,tel);
      dicio_insere_pessoaNumCel(dici,pes);
    }
    if(strcmp(op,"su")==0)
      dicio_insere_cpf_sercomtuel(dici,cpf,numcel);
    else if(strcmp(op,"um")==0)
      dicio_insere_cpf_uelmobile(dici,cpf,numcel);
    else
      printf("Erro na leitura de TM\n");
  }
  return cid;
}

Cidade processoEc(Cidade cid){
  char op, face;
  char codt[30], desc[100];
  char cep[20], cnpj[20], nome[30];
  int num;
  FILE *arq;
  Dicionario dici;
  Estab est;
  dici = getDicionario(cid);
  arq = getArchEc(cid);
  while(!feof(arq)){
    fscanf(arq,"%c ", &op);
    switch(op){
      case 't':
        fscanf(arq,"%s %s", codt, desc);
        dicio_insere_Desctype(dici, desc, codt);
        break;
      case 'e':
        fscanf(arq,"%s %s %s %d %s %s", codt, cep, &face, &num, cnpj, nome);
        est = estab_create(cnpj,nome,codt,cep,face,num);
        dicio_insere_estType(dici,est,codt);
        break;
      default:
        break;
    }
  }
  return cid;
}
