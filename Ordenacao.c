#include <stdio.h>
#include <stdlib.h>
#include "Ordenacao.h"

/*atan2((y2-y1),(x2-x1))
calculo angulo.
Onde o (x1,y1) é do menor y e o (x2,y2)
é do ponto a ser analisado*/

vectorNode *quicksort(vectorNode vector[],int low, int high){
  int n;
  if(low<high){
    n = partition(vector, low, high);
    quicksort(vector, low, n-1);
    quicksort(vector, n+1, high);
  }
}

void swap(vectorNode vector[], int i, int j){
  void *aux;
  double auxX, auxY, auxAng;
  aux = vector[i].ptr;
  auxX = vector[i].x;
  auxY = vector[i].y;
  auxAng = vector[i].ang;

  vector[i].ptr = vector[j].ptr;
  vector[i].x =  vector[j].x;
  vector[i].y = vector[j].y;
  vector[i].ang = vector[j].ang;

  vector[j].ptr = aux;
  vector[j].x = auxX;
  vector[j].y = auxY;
  vector[j].ang = auxAng;
}

int partition(vectorNode vector[],int low,int high){
  int i, j;
  vectorNode *pivot;
  pivot = &vector[high];
  i = (low-1);
  for(j=low;j<=high-1;j++){
    if(vector[j].ang<=pivot->ang){/*vector[j]<=pivot*/
      i++;
      swap(vector, i, j);
    }
  }
  i++;
  swap(vector, i , high);
  return(i);
}

void printTest(vectorNode *vector, int size){
  int i;
  for(i=0;i<size;i++){
    printf("\n%d-vector.x: %f vector.y: %f vector.ang: %f", i, vector[i].x, vector[i].y, vector[i].ang);
  }
}
