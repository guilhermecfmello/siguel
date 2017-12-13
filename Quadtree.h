#ifndef QUADTREE_H
#define QUADTREE_H

typedef void *Tree;
typedef void *Posic;
typedef void *Content;

/*TAD QUADTREE
QUADTREE EH UMA ARVORE QUE ORGANIZA OS DADOS COM BASE EM SUAS
COORDENADAS E REGIOS NO PLANO BIDIMENSIONAL, QUE PODEM SER:
NORDESTE (NE), NOROESTE (NW), SUDOESTE(SW) E SUDESTE (SE).

TREE: ARVORE
POSIC: NO DA ARVORE
CONTENT: CONTEUDO GUARDADO PELO NO.
*/

Tree quadtree_create();
/*Cria e retorna uma quadtree
*/


Posic quadtree_add(Tree t, Content c, double x, double y);
/*Recebe uma arvore nao nula e um conteudo.
Adiciona a essa arvore o conteudo passado.
*/

Posic quadtree_getRoot(Tree t);
/*Recebe uma arvore.
Retorna sua raiz, caso nao tenha, retorna NULL
*/

Posic quadtree_getNodeNE(Tree t, Posic p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante NE do no passado,
caso nao haja, retorna NULL.
*/

Posic quadtree_getNodeSE(Tree t, Posic p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante SE do ono passado,
caso nao haja, retorna NULL.
*/

Posic quadtree_getNodeNW(Tree t, Posic p);
/*Recebe uma arvore e um No dela
Retorna o No filho que estaPosic quadtree_add(Tree t, Content c, double x, double y);
 no quadrante NW do no passado,
caso nao haja, retorna NULL.
*/

Posic quadtree_getNodeSW(Tree t, Posic p);
/*Recebe uma arvore e um No dela
Retorna o No filho que esta no quadrante SW do no passado,
caso nao haja, retorna NULL.Posic quadtree_add(Tree t, Content c, double x, double y);

*/
Content quadtree_get(Posic p);
/*Recebe uma arvore e um no,
retorna o conteudo do no passado.
*/

int quadtree_isLeaf(Tree t, Posic p);
/*Recebe uma arvore e um No.
Retorna 1 caso o no seja uma folha, e 0 caso nao seja.
*/

int quadtree_remove(Tree t, Posic p);
/*Recebe uma arvore e um no.
Remove o no passado da arvore. retorna 1 caso a operacao de certo, 0 caso contrario.
*/

int quadtree_compareQuad(Posic p1, Posic p2);
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

Posic quadtree_down(Tree t, Posic p1, Posic p2);
/*RECEBE UMA ARVORE E DOIS NOS DELA.
RETORNA O PROXIMO NO DE P1 QUE ESTEJA EM DIRECAO AO P2.
*/

int quadtree_removeWithPre(Tree t, Posic pBef, Posic p);
/*REMOVE
*/

void quadtree_print(Posic p);
#endif
