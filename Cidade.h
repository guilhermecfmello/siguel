#ifndef CIDADE__H
#define CIDADE__H
#include "Quadra.h"
#include "Lista.h"
#include "Quadra.h"
#include "Semaforo.h"
#include "Torre.h"
#include "Hidrante.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Quadtree.h"

/*CIDADE É FORMADA POR UM CONJUNTO DE QUADRAS, HIDRANTES, SEMAFOROS E TORRES.
POSSUI OPERACOES PARA LIDAR COM INSERCAO, REMOCAO E BUSCA DE CADA ELEMENTO.*/

typedef void* Cidade;

typedef void (*RecursiveSearchPtrRet)(Posic, Rect, Tree, Posic);
/*MODELO DE FUNCAO PARA SER PASSADA EM ALGUMAS BUSCAR NA CIDADE, NA QUAL PRECISA
BUSCAR ELEMENTOS QUE ESTAO CONTIDOS EM DETERMINADOS RETANGULOS
ELA RECEBE PRIMEIRO O NO INICIAL DA ARVORE, O RETANGULO DE VERIFICACAO, A ARVORE
E O ULTIMO POSIC SERA ALTERADO COMO REFERENCIA, EH NELE QUE FICAR AO ELEMENTO, SE ESTE
EXISTIR
*/
typedef void (*RecursiveSearchPtrCirc)(Posic, Rect, Tree, Posic);
/*MODELO DE FUNCAO PARA SER PASSADA EM ALGUMAS BUSCAR NA CIDADE, NA QUAL PRECISA
BUSCAR ELEMENTOS QUE ESTAO CONTIDOS EM DETERMINADOS CIRCULOS
ELA RECEBE PRIMEIRO O NO INICIAL DA ARVORE, O RETANGULO DE VERIFICACAO, A ARVORE
E O ULTIMO POSIC SERA ALTERADO COMO REFERENCIA, EH NELE QUE FICAR AO ELEMENTO, SE ESTE
EXISTIR
*/
Cidade createCidade();
/*Cria uma cidade e retorna o ponteiro para a própria
*/
Quadra insereQuadra(Cidade c, Quadra q);
/*Recebe uma cidade C e uma Quadra.
Adiciona a Quadra à cidade e retorna um ponteiro para a mesma.
*/
Hidrante insereHidrante(Cidade c, Hidrante h);
/*Recebe uma cidade e um Hidrante
Adiciona o hidrante na Cidade e retorna um ponteiro para o mesmo.
*/
Semaforo insereSemaforo(Cidade c, Semaforo s);
/*Recebe uma cidade e um semaforo,
Adiciona o Semaforo na cidade e retorna um ponteiro para o mesmo.
*/
Torre insereTorre(Cidade c, Torre t);
/*Recebe uma cidade e uma torre,
Adiciona a torre na cidade e retorna um ponteiro para a torre.
*/
Circle insereCirculo(Cidade c, Circle circul);
/*Insere um circulo semantico na Cidade.
*/
Rect insereRetangulo(Cidade c, Rect retan);
/*Insere um retangulo semantico na Cidade,
*/
Rect insereSob(Cidade c, Rect retan);
/*Insere um retangulo que marca sobreposicao semantica na Cidade,
*/
Circle getCirculos(Cidade c);

Rect getRetangulos(Cidade c);

Rect getSobs(Cidade c);

void setCoresQuadras(Cidade c, char *cfill, char *cstrk);
/*Recebe uma cidade C e duas strings. A primeira referencia a cor do preenchimento
da quadra e a segunda a cor da linha. As cores devem estar no padrao SVG.
Configura as cores das quadras com as cores passadas.
*/

void setCoresHidrantes(Cidade c, char *cfill, char *cstrk);
/*Recebe uma cidade C e duas strings. A primeira referencia a cor do preenchimento
do hidrante e a segunda a cor da linha. As cores devem estar no padrao SVG.
Configura as cores dos hidrantes com as cores passadas.
*/
void setCoresTorres(Cidade c, char *cfill, char *cstrk);
/*Recebe uma cidade C e duas strings. A primeira referencia a cor do preenchimento
da torre e a segunda a cor da linha. As cores devem estar no padrao SVG.
Configura as cores das torres com as cores passadas.
*/

void setCoresSemaforos(Cidade c, char *cfill, char *cstrk);
/*Recebe uma cidade C e duas strings. A primeira referencia a cor do preenchimento
dos semaforos e a segunda a cor da linha. As cores devem estar no padrao SVG.
Configura as cores dos semaforos com as cores passadas.
*/

void imprimeQuadrasSvg(Cidade c, FILE *arq);
/*Recebe um arquivo já aberto e uma cidade,
Imprime no arquivo as quadras da cidade.
*/
void imprimeHidrantesSvg(Cidade c, FILE *arq);
/*Recebe um arquivo já aberto e uma cidade,
Imprime no arquivo os hidrantes da cidade*/
void imprimeSemaforosSvg(Cidade c, FILE *arq);
/*Recebe um arquivo já aberto e uma cidade,
Imprime no arquivo os semaforos da cidade*/
void imprimeTorresSvg(Cidade c, FILE *arq);
/*Recebe um arquivo já aberto e uma cidade,
Imprime no arquivo as torres da cidade*/

int getNumQuadras(Cidade c);
/*Recebe uma cidade
Retorna o numero de quadras que esta possui;
*/

Quadra getQuadraRet(Cidade cid, Rect r);

/*Quadra getQuadraRet(Cidade c, Rect r, int *comp);
Recebe um retangulo e uma cidade.
Retorna uma quadra qualquer que esteja contida no retangulo passado.
Caso nao haja quadras, retorna NULL.
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Quadra getQuadraCirc(Cidade c,Circle circ);
/*Quadra getQuadraCirc(Cidade c, Circle circ, int *comp);
Recebe um Circulo e uma cidade.
Retorna uma quadra qualquer que esteja contida no circulo passado.
Caso nao haja quadras contidas, retorna NULL.
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.
*/

Hidrante getHidranteRet(Cidade c, Rect r);
/*Recebe uma cidade e um retangulo
Retorna um hidrante qualquer que esteja contido no retangulo passado.
Caso nao haja Hidrante contido, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Hidrante getHidranteCirc(Cidade c, Circle circ);
/*Recebe uma cidade e um circulo
Retorna um hidrante qualquer que esteja contido no circulo passado.
Caso nao haja hidrante contido, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Semaforo getSemaforoRet(Cidade c, Rect r);
/*Recebe uma cidade e um retangulo
Retorna um semaforo qualquer que esteja contido no retangulo passado.
Caso nao haja semaforo contido, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Semaforo getSemaforoCirc(Cidade c, Circle circ);
/*Recebe uma cidade e um circulo
Retorna um semaforo qualquer que esteja contido no circulo passado.
Caso nao haja semaforo contido, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Torre getTorreRet(Cidade c, Rect r);
/*Recebe uma cidade e um retangulo
Retorna uma torre qualquer que esteja contida no retangulo passado.
Caso nao haja Torre contida, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.

*/

Torre getTorreCirc(Cidade c, Circle circ);
/*Recebe uma cidade e um circulo
Retorna uma torre qualquer que esteja contida no circulo passado.
Caso nao haja torre, retorna NULL
Tambem retorna como referencia em *comp o numero de comparacoes feitas para encontrar o objeto.
*/

void removeQuadra(Cidade c, Quadra q);
/*Recebe uma Cidade e uma quadra
Remove a quadra da cidade.
*/
void removeHidrante(Cidade c, Hidrante h);
/*Recebe uma Cidade e um hidrante
Remove o hidrante da cidade.
*/
void removeSemaforo(Cidade c, Semaforo s);
/*Recebe uma Cidade e um semaforo
Remove o semaforo da cidade.
*/
void removeTorre(Cidade c, Torre t);
/*Recebe uma Cidade e uma torre
Remove a torre da cidade.
*/

Quadra procuraQuadra(Cidade c, char *end);
/*Recebe uma cidade e um endereco.
Retorna a Quadra da cidade que for referenciada por este endereco.
Caso nao encontre, retorna NULL.
*/

Hidrante procuraHidrante(Cidade c, char *end);
/*Recebe uma cidade e um endereco.
Retorna o Hidrante da cidade que for referenciado por este endereco.
Caso nao encontre, retorna NULL.
*/

Semaforo procuraSemaforo(Cidade c, char *end);
/*Recebe uma cidade e um endereco.
Retorna o semaforo da cidade que for referenciado por este endereco.
Caso nao encontre, retorna NULL.
*/
Torre procuraTorreList(Cidade c, char *end);

Torre procuraTorre(Cidade c, char *end);
/*Recebe uma cidade e um endereco.
Retorna o semaforo da cidade que for referenciado por este endereco.
Caso nao encontre, retorna NULL.
*/
Posic procuraElemento(Cidade c, char *end, char *typeElement);
/*Recebe uma cidade, um endereco e uma referencia pro tipo de elemento.
A cidade passada possui um endereco diferente para cada elemento.
Procura na cidade um elemento que seja referenciado pelo endereco passado.
Caso seja uma quadra: Retorna a quadra encontrada e o caractere 'q' como referencia.
Caso seja um semaforo: Retorna o semaforo encontrado e o caractere 's' como referencia.
Caso seja um hidrante: Retorna o hidrante encontrado e o caractere 'h' como referencia.
Caso seja uma torre: Retorna a torre encontrada e o caractere 't' como referencia.
*/
void openArchAreaTorres(char *patch, char *nome, char *nomeQry, char *sufixo,Cidade c);


void openArchSvg(char *patch, char *nome, char *qry, Cidade c);
/*Abre um arquivo de saida svg na cidade, no caminho descrito por patch, com o nome descrito por "nome"
Arquivo somente de escrita.
Neste arquivo sera renderizada a cidade na forma de SVG, que deve ser
interpretada por navegadores ou outros programas affins.
*/

void openArchTxtCons(char *patch, char *nome, char *qry, Cidade c);
/*Abre um arquivo de modo escrita na Cidade.
O arquivo sera criado no diretorio definido por "Patch" e com o nome "nome"."Nome" deve estar sem extencao do arquivo.
Neste arquivo serão escritas as consultas como "Sobreposicao, intercecção, ..."
*/

void openArchTxtComp(char *patch, char *nome, char *type, Cidade c);
/*Cria um arquivo txt na cidade no modo escrita.
Este arquivo sera escrito no diretorio definido por "patch" com o nome "nome"
O arquivo contera o numero de comparacoes feitas para inserir/remover quadras.
*/

void openArchGeo(char *patch, char *nome, Cidade c);
/*Abre um arquivo .geo em modo leitura.
Caso haja patch, concatena-o com nome ao final. Este sera o diretorio com o nome do arquivo.
Caso nao haja patch, assume-se que o caminho dado pelo argumento no nome é completo.
*/

void openArchQry(char *patch, char *nome, Cidade c);
/*Abre um arquivo Qry em modo de leitura
Caso haja um patch, concatena-o com o nome
Caso nao haja, assume-se que o nome possui o diretorio completo
*/

void closeArchAreaTorres(Cidade c);

void closeArchSvg(Cidade c);
/*Escreve no arquivo ArchSvg da cidade a tag de fechamento do Svg
Fecha o arquivo arch Svg da cidade*/

void closeArchTxtCons(Cidade c);
/*Fecha o arquivo ArchTxtCons da Cidade*/

void closeArchTxtComp(Cidade c);
/*Fecha o arquivo ArchTxtComp da Cidade*/

void closeArchQry(Cidade c);
/*Fecha o arquivo de leitura .qry*/

void closeArchGeo(Cidade c);
/*Fecha o arquivo de leitura .geo*/

FILE *getArchGeo(Cidade c);
/*Recebe uma cidade
Retorna seu arquivo GEO
Retorna NULL se o arquivo estiver fechado*/

FILE *getArchTxtCons(Cidade c);
/*Recebe uma cidade
Retorna o seu arquivo de saida Txt de consultas.
Retorna NULL caso o arquivo esteja fechado.
*/

FILE *getArchTxtComp(Cidade c);
/*Recebe uma cidade
Retorna o seu arquivo de saida Txt de comparacoes.
Retorna NULL caso o arquivo esteja fechado.
*/

FILE *getArchQry(Cidade c);
/*Recebe uma cidade
Retorna o seu arquivo de entrada GEO.
Retorna NULL caso o arquivo esteja fechado.
*/

FILE *getArchAreaTorres(Cidade c);

FILE *getArchSvg(Cidade c);
/*Recebe uma cidade
Retorna o seu arquivo de saida Svg.
Retorna NULL caso o arquivo esteja fechado.
*/
Quadra getQuadrasList(Cidade cid);

Torre getTorresList(Cidade cid);

Semaforo getSemaforosList(Cidade cid);

Hidrante getHidrantesList(Cidade cid);

Tree setQuadrasQuadTree(Cidade cid, Tree t);

Tree setSemaforosQuadTree(Cidade cid, Tree t);

Tree setHidrantesQuadTree(Cidade cid, Tree t);

Tree setTorresQuadTree(Cidade cid, Tree t);

Quadra getQuadras(Cidade cid);
/*funcao usada na "GETELEMENTRET", EH A FUNCAO RECURSIVA DE BUSCA DE
QUADRA QUE ESTEJA DENTRO DO RETANGULO PASSADO.
*/
Quadra getQuadras(Cidade cid);

void LimpaListas(Cidade cid);

void getTorreRetRecursive(Posic node, Rect r, Tree t, Torre *tor);

Tree getTorresTree(Cidade c);
#endif
