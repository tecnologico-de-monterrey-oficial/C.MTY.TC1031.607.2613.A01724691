# Evidencia 1 — Ordenamiento y búsqueda en logs de seguridad

Aplicación en C++ que lee un log de eventos de seguridad, lo ordena cronológicamente
con distintos algoritmos y permite comparar su desempeño.

## Estructura de carpetas

| Carpeta | Para qué sirve |
|---|---|
| `data/` | Archivos de entrada: `log607-1.txt` (desordenado) y `log607-2.txt` (casi ordenado). Aquí no se escribe nada, solo se lee. |
| `src/` | Código fuente principal. Contiene `main.cpp`, que es el menú y el flujo del programa. |
| `include/` | Archivos de cabecera con la lógica separada: `Registro.h` (estructura del registro, lectura y escritura de archivos) y `Ordenamientos.h` (los 7 algoritmos de ordenamiento). |
| `docs/` | Documentación y entregables: `ReflexEvidencia1.pdf` y `EvidenciasPruebas.pdf`. |
| `build/` | Salida de la compilación (el ejecutable). No se sube a git. |
| `out/` | Salidas que genera la app: `output608.txt` (datos ordenados de la última corrida), `resultados608.txt` (bitácora de todas las corridas) y `range607.txt` (resultado de la búsqueda por rango). |
| `scripts/` | Scripts para compilar y ejecutar sin escribir el comando completo. |

## Cómo compilar y ejecutar

Desde la carpeta `Evidence1`:

```bash
g++ -std=c++11 -O2 -Iinclude src/main.cpp -o build/evidencia1.exe
./build/evidencia1.exe
```

O usando los scripts:

```bash
bash scripts/compilar.sh
bash scripts/ejecutar.sh
```

Importante: el programa debe ejecutarse **desde la carpeta `Evidence1`**, porque
busca los archivos en `data/` y escribe en `out/` con rutas relativas.

## Formato de fechas esperado

Cada línea del log tiene esta forma:

```
Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts
```

- **Mes**: tres letras en inglés (`Jan`, `Feb`, `Mar`, ..., `Dec`)
- **Día**: dos dígitos (`01` a `31`)
- **Año**: cuatro dígitos
- **Hora**: `HH:MM:SS` en formato de 24 horas
- **IP**: dirección IPv4
- **Razón**: texto libre, puede tener varias palabras

Internamente cada fecha se convierte a un número con la forma `AAAAMMDDHHMMSS`,
para poder comparar dos fechas completas con un simple `<` o `>`.

## Uso de la aplicación

1. Elegir el archivo a procesar (`log607-1.txt` o `log607-2.txt`).
2. Elegir el algoritmo de ordenamiento (swapSort, selectionSort, bubbleSort,
   insertionSort, mergeSort, quickSort, shellSort).
3. Dar una predicción de si será rápido o lento y por qué.
4. El programa ordena, mide el tiempo y muestra el reporte con la complejidad
   teórica y si la predicción coincidió.
5. El menú se repite para poder comparar sin reiniciar el programa.

## Política de uso de IA

Se usó asistencia de IA (Claude) para:

- Generar el esqueleto del parser de las líneas del log y el menú.
- Revisar la implementación de los algoritmos y detectar riesgos, como el
  desbordamiento de pila de quickSort con pivote fijo sobre datos casi ordenados.
- Redactar esta documentación.

No se usó IA para:

- Inventar tiempos o resultados de las pruebas. Todos los tiempos reportados en
  `out/resultados608.txt` salieron de correr el programa con los archivos reales.
- Sustituir el análisis de complejidad, que se justifica en la reflexión.

Todo el código fue revisado y probado antes de entregarse.
