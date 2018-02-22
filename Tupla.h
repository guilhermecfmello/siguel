#ifndef TUPLA__H
#define TUPLA__H

typedef void* Tupla;

Tupla tuplas_create();

void tuplas_set_regs(Tupla T, char *registrador, double x, double y);

double tuplas_get_x(Tupla T, char *registrador);

double tuplas_get_y(Tupla T, char *registrador);

#endif
