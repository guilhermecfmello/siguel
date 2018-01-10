#ifndef QUADTREE_H
#define QUADTREE_H

typedef void *Tree;
typedef void *PosicQ;
typedef void *Content;

/*TAD QUADTREE
QUADTREE EH UMA ARVORE QUE ORGANIZA OS DADOS COM BASE EM SUAS
COORDENADAS E REGIOS NO PLANO BIDIMENSIONAL, QUE PODEM SER:
NORDESTE (NE), NOROESTE (NW), SUDOESTE(SW) E SUDESTE (SE).

TREE: ARVORE
PosicQ: NO DA ARVORE
CONTENT: CONTEUDO GUARDADO PELO NO.
*/

Tree quadtree_create();
/*Cria e retorna uma quadtree
*/


PosicQ quadtree_add(Tree t, Content c, double x, double y);
/*Recebe uma arvore nao nula e um conteudo.
Adiciona a essa arvore o conteudo passado.
*/

PosicQ quadtree_getRoot(Tree t);
/*Recebe uma arvore.
Retorna sua raiz, caso nao tenha, retorna NULL
*/

PosicQ quadtree_getNodeNE(Tree t, PosicQ p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante NE do no passado,
caso nao haja, retorna NULL.
*/

PosicQ quadtree_getNodeSE(Tree t, PosicQ p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante SE do ono passado,
caso nao haja, retorna NULL.
*/

PosicQ quadtree_getNodeNW(Tree t, PosicQ p);
/*Recebe uma arvore e um No dela
Retorna o No filho que estaPosicQ quadtree_add(Tree t, Content c, double x, double y);
 no quadrante NW do no passado,
caso nao haja, retorna NULL.
*/

PosicQ quadtree_getNodeSW(Tree t, PosicQ p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante SW do no passado,
caso nao haja, retorna NULL.PosicQ quadtree_add(Tree t, Content c, double x, double y);

*/
Content quadtree_get(PosicQ p);
/*Recebe uma arvore e um no,
retorna o conteudo do no passado.
*/

int quadtree_isLeaf(Tree t, PosicQ p);
/*Recebe uma arvore e um No.
Retorna 1 caso o no seja uma folha, e 0 caso nao seja.
*/

int quadtree_remove(Tree t, PosicQ p);
/*Recebe uma arvore e um no.
Remove o no passado da arvore. retorna 1 caso a operacao de certo, 0 caso contrario.
*/

int quadtree_compareQuad(PosicQ p1, PosicQ p2);
/*Recebe dois nos de uma arvore.
Retorna o quadrante em que o no p2 esta em relacao ao p1, em numero inteiro.
  NW: 1;
  NE: 2;
  SW: 3;
  SE: 4;
  default: -1;
*/
int quadtree_getHeight(Tree t);
/*RECEBE UMA ARVORE
RETORNA SUA ALTURA, OU SEJA, A DISTANCIA ENTRE SUA RAIZ E A SUA FOLHA
*/
int quadtree_getSize(Tree t);
/*RECEBE UMA ARVORE
RETORNA O NUMERO DE ELEMENTOS QUE ELA CARREGA.
*/

PosicQ quadtree_down(Tree t, PosicQ p1, PosicQ p2);
/*RECEBE UMA ARVORE E DOIS NOS DELA.
RETORNA O PROXIMO NO DE P1 QUE ESTEJA EM DIRECAO AO P2.
*/

int quadtree_removeWithPre(Tree t, PosicQ pBef, PosicQ p);
/*REMOVE
*/

void quadtree_print(PosicQ p);

void quadtree_percorre(Tree t, PosicQ p);
/*Recebe uma arvore e um no dela.
Retorna algum no filho que ela tenha, com a seguinte prioridade:
1.NW 2.NE 3.SW 4.SE
*/

int getCompsIns(Tree t1);
/*Recebe uma arvore não nula,
retorna o numero de comparacoes feitas para inserir todos os elementos dela.
*/
int getCompsRem(Tree t1);
/*Recebe uma arvore não nula,
retorna o numero de comparacoes feitas para remover os elementos selecionados.
*/
#endif
