#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Escrita.h"

char *filtraNome(char *c){
  int size, i,j;
  char *newName;
  size = strlen(c);
  i = size-1;
  j=0;
  while(c[i]!='/'){
    i--;
    j++;
    if(i==0){
      i--;
      break;
    }
  }
  newName = (char *) malloc(sizeof(char)*j+2);
  j=0;
  i++;
  for(;i<size;i++){
    newName[j] = c[i];
    j++;
  }
  newName[j] = '\0';
  return newName;
}

char *makeTxt(char *c){
  int size;
  char *newName;
  size = strlen(c);
  newName = malloc(sizeof(char)*(size+1));
	strcpy(newName,c);
  size = size - 4;
  newName[size] = '.';
  size++;
  newName[size] = 't';
  size++;
  newName[size] = 'x';
  size++;
  newName[size] = 't';
	size++;
	newName[size] = '\0';
  return newName;
}

char *makeSvg(char *c){
  int size;
  char *newName;
  size = strlen(c);
  newName = malloc(sizeof(char)*(size+1));
	strcpy(newName,c);
  size = size - 4;
  newName[size] = '.';
  size++;
  newName[size] = 's';
  size++;
  newName[size] = 'v';
  size++;
  newName[size] = 'g';
	size++;
	newName[size] = '\0';
  return newName;
}

char *makeSaidaComSufixo(char *sufixo, char *nome){
  char *newName;
  int sizeSuf, sizeNome, i, j;
  sizeSuf = strlen(sufixo);
  sizeNome = strlen(nome);
  newName = malloc(sizeof(char)*(sizeSuf+sizeNome-1));
  strcpy(newName,nome);
  i = sizeNome-4;
  newName[i++]='-';
  sizeNome = sizeSuf+sizeNome-2;
  j=0;
  for(;i<sizeNome;i++){
    newName[i] = sufixo[j++];
  }
  newName[i] = '\0';
  return newName;
}

char *colocaDiretorio(char *arquivo, char *diretorio){
  int size, i, j;
  char *newName;
  i = strlen(diretorio)-1;
  if(diretorio[i]=='/'){
    size = strlen(diretorio) + strlen(arquivo) + 1;
    newName = malloc(sizeof(char)*size);
    strcpy(newName,diretorio);
    i = strlen(diretorio);
    j=0;
    for(;i<size-1;i++){
      newName[i] = arquivo[j];
      j++;
    }
    newName[i] = '\0';
  }
  else{
    size = strlen(diretorio) + strlen(arquivo) + 2;
    newName = malloc(sizeof(char)*size);
    strcpy(newName,diretorio);
    j=0;
    i = strlen(diretorio);
    newName[i] = '/';
    i++;
    for(;i<size-1;i++){
      newName[i] = arquivo[j];
      j++;
    }
    newName[i] = '\0';
  }
  return newName;
}

char *addSvg(char *content){
  int i, size;
  char *newName, svg[5];
  strcpy(svg,".svg");
  size = strlen(content);
  newName = malloc(sizeof(char)*size+5);
  strcpy(newName,content);
  for(i=0;i<4;i++){
    newName[size]=svg[i];
    size++;
  }
  newName[size] = '\0';
  return newName;
}

char *removeExtensao(char *c){
  int size, i, j;
  char *aux;
  size = strlen(c);
  aux = malloc(sizeof(char)*(size-3));
  for(i=0;i<size-4;i++){
    aux[i] = c[i];
  }
  aux[i] = '\0';
  return aux;
}

char *colocaBarra(char *c){
  int size, i;
  char *newString;
  if(c!=NULL){
    size = strlen(c);
    if(c[size-1]!='/'){
      newString = malloc(sizeof(char)*((size)+2));
      strcpy(newString,c);
      newString[size] = '/';
      newString[size+1] = '\0';
      return newString;
    }
    return c;
  }
}
