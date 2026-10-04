/*
 * medicion.h
 * Funciones de ayuda para medir el tiempo de ejecucion de los programas
 * del Laboratorio 8 (Teoria de la computacion).
 */

#ifndef MEDICION_H
#define MEDICION_H

#include <stdio.h>
#include <time.h>

/* Valores de n que pide el laboratorio. */
#define CANTIDAD_VALORES 7
static const int VALORES_N[CANTIDAD_VALORES] = {
    1, 10, 100, 1000, 10000, 100000, 1000000
};

/* Si una ejecucion dura menos que este tiempo (en segundos), se repite
   varias veces y se calcula el promedio, para que la medicion sea
   mas confiable. */
#define TIEMPO_MINIMO 0.05

/* Limite de repeticiones para las funciones muy rapidas. */
#define MAX_REPETICIONES 1000000

/*
 * Mide cuantos segundos tarda funcion(n).
 * Si la funcion es muy rapida, la ejecuta varias veces y devuelve el
 * tiempo promedio de una sola ejecucion.
 */
static double medir_tiempo(void (*funcion)(int), int n)
{
    clock_t inicio, fin;
    double segundos;
    long repeticiones = 1;
    long i;

    /* Se duplican las repeticiones hasta que el tiempo total supere
       TIEMPO_MINIMO. Asi no se depende de estimar el tiempo de una
       sola llamada, que con la resolucion de clock() puede dar 0. */
    while (1) {
        inicio = clock();
        for (i = 0; i < repeticiones; i++) {
            funcion(n);
        }
        fin = clock();

        segundos = (double)(fin - inicio) / CLOCKS_PER_SEC;
        if (segundos >= TIEMPO_MINIMO || repeticiones >= MAX_REPETICIONES) {
            break;
        }
        repeticiones *= 2;
    }

    return segundos / repeticiones;
}

/*
 * Envia lo que se imprima con printf a "ninguna parte", para que el
 * tiempo medido no dependa de la velocidad de la pantalla.
 * Los resultados del programa se muestran con stderr.
 */
static inline void descartar_salida_estandar(void)
{
#ifdef _WIN32
    const char *destino = "NUL";
#else
    const char *destino = "/dev/null";
#endif

    if (freopen(destino, "w", stdout) == NULL) {
        fprintf(stderr, "No se pudo descartar la salida estandar.\n");
    }
}

#endif
