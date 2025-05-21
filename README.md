# Algoritmos K-Means, Prim y Kruskal en C++

## Autor
- **Angel Burbano**

## Descripción
Este proyecto implementa tres algoritmos fundamentales en C++:

### 1. K-Means Clustering
- Algoritmo de agrupamiento no supervisado.
- Clasifica puntos en `k` grupos (clústeres) según similitud (distancia euclidiana).
- Lee datos desde un archivo `kmeans.txt` y agrupa basándose en características seleccionadas.
- Imprime los puntos agrupados, los tamaños de clústeres y los centroides finales.

### 2. Kruskal (Árbol de Expansión Mínima)
- Algoritmo de grafos para encontrar un árbol de expansión mínima.
- Utiliza la técnica de **Union-Find** para evitar ciclos.
- Las aristas se ordenan por peso y se agregan si no forman ciclos.
- Imprime las aristas seleccionadas y el peso total del MST (Minimum Spanning Tree).

### 3. Prim (Árbol de Expansión Mínima)
- Algoritmo alternativo a Kruskal para hallar un MST.
- Se expande el árbol desde un nodo inicial seleccionando la arista más barata hacia un nodo no incluido.
- Imprime las aristas seleccionadas y el peso total del árbol.

## Archivos
- `k-means.cc`: Implementación del algoritmo de K-Means.
- `kruskal.cc`: Implementación del algoritmo de Kruskal.
- `prim.cc`: Implementación del algoritmo de Prim.
- `kmeans.txt`: Archivo de entrada con datos tabulados para el K-Means.
  
