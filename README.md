# Laboratorio 8 - Teoría de la computación

Análisis de la complejidad de tiempo de varios programas. El repositorio
contiene el código en C con el que se midieron los tiempos de ejecución
y el documento PDF con las respuestas de los ejercicios sin código.

## Contenido del repositorio

```
.
├── README.md
├── src/
│   ├── medicion.h          funciones para medir tiempos (usadas por los 3 programas)
│   ├── problema1.c         Problema 1, parte b
│   ├── problema2.c         Problema 2, parte b
│   ├── problema3.c         Problema 3, parte b
│   └── analisis.py         genera las tablas y las gráficas a partir de los CSV
├── resultados/             archivos CSV, tablas y gráficas generadas
└── respuestas_pdf/         respuestas de los ejercicios sin código (PDF)
```

## Requisitos

- Compilador de C (`gcc`). En Windows se puede usar MinGW.
- Python 3 con la librería `matplotlib` (solo para generar las gráficas):

```
pip install matplotlib
```

## Instrucciones de ejecución

Todos los comandos se ejecutan desde la carpeta principal del repositorio.

### 1. Compilar

Se usa `-O0` (sin optimización) para que el compilador no elimine los
ciclos y así se mida el trabajo real de cada programa.

```
gcc -O0 -Wall -o problema1 src/problema1.c
gcc -O0 -Wall -o problema2 src/problema2.c
gcc -O0 -Wall -o problema3 src/problema3.c
```

### 2. Ejecutar

```
./problema1
./problema2
./problema3
```

En Windows se ejecutan como `problema1.exe`, `problema2.exe` y `problema3.exe`.

Cada programa mide el tiempo para n = 1, 10, 100, 1000, 10000, 100000 y
1000000, muestra una tabla en pantalla y guarda los datos en
`resultados/problemaX.csv`.

Los programas de los problemas 2 y 3 imprimen `Sequence` muchas veces; esa
salida se descarta automáticamente para que el tiempo medido no dependa de
la pantalla.

### 3. Generar tablas y gráficas

```
python3 src/analisis.py
```

Esto crea, dentro de `resultados/`, un archivo `resumen_problemaX.csv` con la
tabla y una imagen `grafica_problemaX.png` con la gráfica de tamaño de input
contra tiempo para cada problema.

## Tiempos de ejecución y valores omitidos

Algunos valores de n tardan mucho tiempo en medirse. Por eso cada programa
tiene un valor máximo de n por defecto:

- El problema 1 mide por defecto hasta n = 100000. Si n = 1000000 no se
  mide, aparece como `omitido (ver README para medirlo)`.
- El problema 3 mide por defecto hasta n = 10000. Si n = 100000 y
  n = 1000000 no se miden, aparecen como `omitido por tiempo`.
- El problema 2 mide todos los valores.

Para medir también los valores omitidos se indica como argumento el n
máximo, por ejemplo:

```
./problema1 1000000
./problema3 100000
```

Tiempos en la computadora donde se hicieron las pruebas (compilados con
`-O2`; las mediciones marcadas como estimadas salen de `analisis.py` a partir
del mayor n medido):

| Programa   | n = 10000        | n = 100000                    | n = 1000000              |
|------------|------------------|-------------------------------|--------------------------|
| problema1  | 0.107 s          | unos 13 s (estimado)          | unos 25 min (estimado)   |
| problema2  | 0.004 s          | 0.040 s                       | 0.376 s                  |
| problema3  | 3.16 s           | unos 5 min 16 s (medido) (*)  | unas 8.6 horas (estimado)|

(*) Medido en una corrida anterior del mismo programa; con el valor por
defecto actual de `problema3` no se mide.

Si un valor de n no se mide, `analisis.py` lo estima multiplicando el tiempo
del mayor n medido por la proporción de operaciones que predice el análisis
teórico. Esos valores aparecen marcados como `estimado` en las tablas y con
un círculo vacío en las gráficas. Los valores medidos aparecen como `medido`.

## Respuestas sin código

El documento con el análisis teórico de los problemas 1, 2 y 3 (parte a),
el problema 4, el problema 5 y los resultados de las mediciones está en la
carpeta `respuestas_pdf/`.

## Video

https://youtu.be/BtFbeblp3Q0
