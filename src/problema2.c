/*
 * problema2.c
 * Laboratorio 8 - Problema 2, parte b
 *
 * Mide el tiempo de ejecucion de la funcion del problema 2 para
 * n = 1, 10, 100, 1000, 10000, 100000 y 1000000.
 *
 * Uso (desde la raiz del repositorio):
 *     ./problema2 [n_maximo]
 *
 * Los resultados se guardan en resultados/problema2.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include "medicion.h"

/* En este problema se pueden medir todos los valores de n. */
#define N_MAXIMO_POR_DEFECTO 1000000

/* Funcion del enunciado. */
void function(int n)
{
    int i, j;

    if (n <= 1) {
        return;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("Sequence\n");
            break;
        }
    }
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

    archivo = fopen("resultados/problema2.csv", "w");
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo crear resultados/problema2.csv\n");
        fprintf(stderr, "Ejecute el programa desde la raiz del repositorio.\n");
        return 1;
    }
    fprintf(archivo, "n,tiempo_segundos\n");

    /* Lo que imprime la funcion no interesa, solo su tiempo. */
    descartar_salida_estandar();

    fprintf(stderr, "Problema 2 - mediciones\n");
    fprintf(stderr, "%10s %16s\n", "n", "tiempo (s)");

    for (p = 0; p < CANTIDAD_VALORES; p++) {
        n = VALORES_N[p];

        if (n > n_maximo) {
            fprintf(stderr, "%10d  omitido (ver README para medirlo)\n", n);
            continue;
        }

        segundos = medir_tiempo(function, n);

        fprintf(stderr, "%10d %16.9f\n", n, segundos);
        fprintf(archivo, "%d,%.9f\n", n, segundos);
    }

    fclose(archivo);
    return 0;
}
