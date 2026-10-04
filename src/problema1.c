/*
 * problema1.c
 * Laboratorio 8 - Problema 1, parte b
 *
 * Mide el tiempo de ejecucion de la funcion del problema 1 para
 * n = 1, 10, 100, 1000, 10000, 100000 y 1000000.
 *
 * Uso (desde la raiz del repositorio):
 *     ./problema1 [n_maximo]
 *
 * Los resultados se guardan en resultados/problema1.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include "medicion.h"

/* Valor maximo de n que se mide si no se indica otro (ver README). */
#define N_MAXIMO_POR_DEFECTO 100000

/* Guarda el valor final de counter para poder mostrarlo despues. */
static long long ultimo_contador = 0;

/*
 * Funcion del enunciado.
 * Se uso long long en counter porque, para n grande, el contador
 * supera el limite de un int.
 */
void function(int n)
{
    int i, j, k;
    long long counter = 0;

    for (i = n / 2; i <= n; i++) {
        for (j = 1; j + n / 2 <= n; j++) {
            for (k = 1; k <= n; k = k * 2) {
                counter++;
            }
        }
    }

    ultimo_contador = counter;
}

int main(int argc, char *argv[])
{
    int n_maximo = N_MAXIMO_POR_DEFECTO;
    int n, p;
    double segundos;
    FILE *archivo;

    if (argc > 1) {
        n_maximo = atoi(argv[1]);
    }

    archivo = fopen("resultados/problema1.csv", "w");
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo crear resultados/problema1.csv\n");
        fprintf(stderr, "Ejecute el programa desde la raiz del repositorio.\n");
        return 1;
    }
    fprintf(archivo, "n,contador,tiempo_segundos\n");

    fprintf(stderr, "Problema 1 - mediciones\n");
    fprintf(stderr, "%10s %18s %16s\n", "n", "contador", "tiempo (s)");

    for (p = 0; p < CANTIDAD_VALORES; p++) {
        n = VALORES_N[p];

        if (n > n_maximo) {
            fprintf(stderr, "%10d  omitido (ver README para medirlo)\n", n);
            continue;
        }

        segundos = medir_tiempo(function, n);

        fprintf(stderr, "%10d %18lld %16.9f\n", n, ultimo_contador, segundos);
        fprintf(archivo, "%d,%lld,%.9f\n", n, ultimo_contador, segundos);
    }

    fclose(archivo);
    return 0;
}
