#ifndef ESCRITA__H
#define ESCRITA__H

char *filtraNome(char *c);
/*Recebe um ponteiro para uma string com o nome de um arquivo e retorna
outro ponteiro para uma string que possui somente o nome limpo do arquivo,
ou seja, sem diretorio.
*/
char *makeTxt(char *c);
/*Recebe um ponteiro para uma string, retorna outra string com os quatro
ultimos caracteres trocados por ".txt"
*/
char *makeSvg(char *c);
/*Recebe um ponteiro para uma string, retorna outra string com os quatro
ultimos caracteres trocados por ".svg"
*/
char *makeSaidaComSufixo(char *sufixo, char *nome);
/*Recebe uma string, concatena o nome com o "-",sufixo.
*/
char *colocaDiretorio(char *arquivo, char *diretorio);
/*Concatena a string "arquivo" a frente da string "diretorio", se diretorio nao
terminar com "/", adiciona.
*/
char *addSvg(char *content);
/*Recebe uma string e cria outra com o conteudo da "content" concatenado com
".svg"
*/

char *removeExtensao(char *c);
/*Recebe um nome de arquivo.
Se houver extensao, retorna um novo nome sem a mesma.
Se nao houver, retorna o mesmo nome passado como parametro.
*/

char *colocaBarra(char *c);
/*Se a string passada nao terminar com barra, coloca uma ao final.
A string deve ter tamanho >=1
*/
#endif
