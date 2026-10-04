/*
 * problema3.c
 * Laboratorio 8 - Problema 3, parte b
 *
 * Mide el tiempo de ejecucion de la funcion del problema 3 para
 * n = 1, 10, 100, 1000, 10000, 100000 y 1000000.
 *
 * Uso (desde la raiz del repositorio):
 *     ./problema3 [n_maximo]
 *
 * Los resultados se guardan en resultados/problema3.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include "medicion.h"

/* Valor maximo de n que se mide si no se indica otro. Con 100000 la
   ejecucion tarda demasiado, asi que ese valor se estima en analisis.py. */
#define N_MAXIMO_POR_DEFECTO 10000

/* Funcion del enunciado. */
void function(int n)
{
    int i, j;

    for (i = 1; i <= n / 3; i++) {
        for (j = 1; j <= n; j += 4) {
            printf("Sequence\n");
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

    archivo = fopen("resultados/problema3.csv", "w");
    if (archivo == NULL) {
        fprintf(stderr, "No se pudo crear resultados/problema3.csv\n");
        fprintf(stderr, "Ejecute el programa desde la raiz del repositorio.\n");
        return 1;
    }
    fprintf(archivo, "n,tiempo_segundos\n");

    /* Lo que imprime la funcion no interesa, solo su tiempo. */
    descartar_salida_estandar();

    fprintf(stderr, "Problema 3 - mediciones\n");
    fprintf(stderr, "%10s %16s\n", "n", "tiempo (s)");

    for (p = 0; p < CANTIDAD_VALORES; p++) {
        n = VALORES_N[p];

        if (n > n_maximo) {
            fprintf(stderr, "%10d  omitido por tiempo\n", n);
            continue;
        }

        segundos = medir_tiempo(function, n);

        fprintf(stderr, "%10d %16.9f\n", n, segundos);
        fprintf(archivo, "%d,%.9f\n", n, segundos);
        /* Se guarda cada fila al momento, por si el programa se interrumpe. */
        fflush(archivo);
    }

    fclose(archivo);
    return 0;
}
