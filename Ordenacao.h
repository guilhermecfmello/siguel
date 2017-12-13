#ifndef ORDENACAO__H
#define ORDENACAO__H

typedef struct _vector{
  void *ptr;
  double x;
  double y;
  double ang;
}vectorNode;
/*NÓ DE CADA ITEM DO VETOR, O PONTEIRO GUARDA O
ELEMENTO GENERICO QUE O VETOR CARREGA*/

/* MODULO DE ORDENACOES
NESTE MODULO SAO IMPLEMENTADOS ALGORITMOS DE ORDENACAO DE VETORES(POR ENQUANTO USAMOS SOMENTE UM)
*/

void swap(vectorNode vector[], int i, int j);
/*TROCA DOIS ELEMENTOS DO VETOR*/


vectorNode *quicksort(vectorNode vector[],int low, int high);
/*RECEBE A FUNCAO DE COMPARACAO, O VETOR A SER ORDENADO E DOIS INTEIROS,
QUE REPRESENTAM O INTERVALO DO VETOR A SER ORDENADO.
RETORNA O VETOR ORDENADO*/

void printTest(vectorNode *vector, int size);


#endif
