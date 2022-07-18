#include <stdio.h>
#include <stdlib.h>

#define DATI 	0
#define ALLOC 	1
#define AP_SCR	2
#define POS	3

void menu(void);
FILE* apertura(FILE* (*tipo) (FILE *fp));
FILE* scrittura_up(FILE *fp);
void clear_buffer(void);
void gest_err(int err);

