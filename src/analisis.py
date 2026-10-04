"""
analisis.py
Laboratorio 8 - Teoria de la computacion

Lee los archivos CSV generados por los programas en C, completa los valores
de n que no se midieron (con una estimacion) y genera, para cada problema,
una tabla y una grafica de tamano de input vs tiempo.

Uso (desde la raiz del repositorio):
    python3 src/analisis.py

Salida (carpeta resultados/):
    resumen_problemaX.csv   tabla con n, operaciones, tiempo y tipo de dato
    grafica_problemaX.png   grafica de n vs tiempo
"""

import csv
import matplotlib

matplotlib.use("Agg")  # permite generar imagenes sin abrir ventanas
import matplotlib.pyplot as plt

VALORES_N = [1, 10, 100, 1000, 10000, 100000, 1000000]


# ---------------------------------------------------------------------------
# Cantidad exacta de operaciones de cada funcion (se obtiene en el PDF)
# ---------------------------------------------------------------------------

def operaciones_problema1(n):
    """Veces que se ejecuta counter++ en el problema 1."""
    iteraciones_i = n - n // 2 + 1
    iteraciones_j = n - n // 2
    iteraciones_k = n.bit_length()  # es igual a floor(log2(n)) + 1
    return iteraciones_i * iteraciones_j * iteraciones_k


def operaciones_problema2(n):
    """Veces que se ejecuta printf en el problema 2."""
    if n <= 1:
        return 0
    return n


def operaciones_problema3(n):
    """Veces que se ejecuta printf en el problema 3."""
    iteraciones_i = n // 3
    iteraciones_j = (n + 3) // 4  # es igual a ceil(n / 4)
    return iteraciones_i * iteraciones_j


# ---------------------------------------------------------------------------
# Lectura y escritura de archivos
# ---------------------------------------------------------------------------

def leer_mediciones(numero):
    """Devuelve un diccionario {n: tiempo} con lo medido por el programa en C."""
    ruta = "resultados/problema" + str(numero) + ".csv"
    tiempos = {}
    contadores = {}

    with open(ruta, newline="") as archivo:
        for fila in csv.DictReader(archivo):
            n = int(fila["n"])
            tiempos[n] = float(fila["tiempo_segundos"])
            if "contador" in fila:
                contadores[n] = int(fila["contador"])

    return tiempos, contadores


def guardar_resumen(numero, filas):
    ruta = "resultados/resumen_problema" + str(numero) + ".csv"
    with open(ruta, "w", newline="") as archivo:
        escritor = csv.writer(archivo)
        escritor.writerow(["n", "operaciones", "tiempo_segundos", "tipo"])
        for fila in filas:
            escritor.writerow(fila)


# ---------------------------------------------------------------------------
# Grafica
# ---------------------------------------------------------------------------

def graficar(numero, filas, constante, operaciones):
    """Grafica n vs tiempo en escala logaritmica."""
    ns_medidos = [f[0] for f in filas if f[3] == "medido"]
    ts_medidos = [f[2] for f in filas if f[3] == "medido"]
    ns_estimados = [f[0] for f in filas if f[3] == "estimado"]
    ts_estimados = [f[2] for f in filas if f[3] == "estimado"]

    # Curva teorica escalada con la constante obtenida del mayor n medido.
    ts_modelo = [constante * max(operaciones(n), 1) for n in VALORES_N]

    plt.figure(figsize=(6.5, 4.2))
    plt.loglog(VALORES_N, ts_modelo, "--", color="gray",
               label="Modelo teórico (escalado)")
    plt.loglog(ns_medidos, ts_medidos, "o-", color="tab:blue",
               label="Tiempo medido")
    if ns_estimados:
        plt.loglog(ns_estimados, ts_estimados, "o", color="tab:red",
                   markerfacecolor="white", label="Tiempo estimado")

    plt.title("Problema " + str(numero) + ": tamaño de input vs tiempo")
    plt.xlabel("Tamaño de input n")
    plt.ylabel("Tiempo de ejecución (s)")
    plt.grid(True, which="both", alpha=0.3)
    plt.legend()
    plt.tight_layout()
    plt.savefig("resultados/grafica_problema" + str(numero) + ".png", dpi=150)
    plt.close()


# ---------------------------------------------------------------------------
# Procesamiento de cada problema
# ---------------------------------------------------------------------------

def procesar_problema(numero, operaciones):
    tiempos, contadores = leer_mediciones(numero)

    # Si el programa guardo el contador, se comprueba contra la formula.
    for n in contadores:
        if contadores[n] != operaciones(n):
            print("ADVERTENCIA: la formula no coincide para n =", n)

    # Constante de proporcionalidad: tiempo por operacion en el mayor n medido.
    n_referencia = max(tiempos)
    constante = tiempos[n_referencia] / operaciones(n_referencia)

    filas = []
    for n in VALORES_N:
        if n in tiempos:
            filas.append([n, operaciones(n), tiempos[n], "medido"])
        else:
            estimado = constante * operaciones(n)
            filas.append([n, operaciones(n), estimado, "estimado"])

    guardar_resumen(numero, filas)
    graficar(numero, filas, constante, operaciones)

    print("Problema", numero)
    print("%10s %16s %16s  %s" % ("n", "operaciones", "tiempo (s)", "tipo"))
    for n, ops, t, tipo in filas:
        print("%10d %16d %16.9f  %s" % (n, ops, t, tipo))
    print()


def main():
    procesar_problema(1, operaciones_problema1)
    procesar_problema(2, operaciones_problema2)
    procesar_problema(3, operaciones_problema3)


main()
