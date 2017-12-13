ARQUIVOS_OBJETOS = Principal.o Procedimentos.o Circulo.o Retangulo.o Lista.o\
Escrita.o Operacoes.o Quadra.o Hidrante.o Torre.o Semaforo.o Cidade.o Formas.o\
Pilha.o Ordenacao.o ConvexHull.o Quadtree.o


siguel: $(ARQUIVOS_OBJETOS)
	gcc -o siguel $(ARQUIVOS_OBJETOS) -lm -g -pedantic -ansi

Principal.o: Principal.c
	gcc -c Principal.c -o Principal.o -g -pedantic -ansi

Ordenacao.o: Ordenacao.c Ordenacao.h
	gcc -c Ordenacao.c -o Ordenacao.o -g -pedantic -ansi

Procedimentos.o: Procedimentos.c Procedimentos.h
	gcc -c Procedimentos.c -o Procedimentos.o -g -pedantic -ansi

Operacoes.o: Operacoes.c Operacoes.h
	gcc -c Operacoes.c -o Operacoes.o -lm -g -pedantic -ansi

Retangulo.o: Retangulo.c Retangulo.h
	gcc -c Retangulo.c -o Retangulo.o -g -pedantic -ansi

Cidade.o: Cidade.c Cidade.h
	gcc -c Cidade.c -o Cidade.o -g -pedantic -ansi

Torre.o: Torre.c Torre.h
	gcc -c Torre.c -o Torre.o -g -pedantic -ansi

Semaforo.o: Semaforo.c Semaforo.h
	gcc -c Semaforo.c -o Semaforo.o -g -pedantic -ansi

Quadra.o: Quadra.c Quadra.h
	gcc -c Quadra.c -o Quadra.o -g -pedantic -ansi

Hidrante.o: Hidrante.c Hidrante.h
	gcc -c Hidrante.c -o Hidrante.o -g -pedantic -ansi

Circulo.o: Circulo.c Circulo.h
	gcc -c Circulo.c -o Circulo.o -g -pedantic -ansi

Formas.o: Formas.c Formas.h
	gcc -c Formas.c -o Formas.o -g -pedantic -ansi

Lista.o: Lista.c Lista.h
	gcc -c Lista.c -o Lista.o -g -pedantic -ansi

Escrita.o: Escrita.c Escrita.h
	gcc -c Escrita.c -o Escrita.o -g -pedantic -ansi

Pilha.o: Pilha.c Pilha.h
	gcc -c Pilha.c -o Pilha.o -g -pedantic -ansi

ConvexHull.o: ConvexHull.c ConvexHull.h
	gcc -c ConvexHull.c -o ConvexHull.o -lm -g -pedantic -ansi

Quadtree.o: Quadtree.c Quadtree.h
	gcc -c Quadtree.c -o Quadtree.o -g -pedantic -ansi

clean:
		rm -rf *.o siguel
