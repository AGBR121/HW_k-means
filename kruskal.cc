#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Clase para representar una arista
class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Unión-Búsqueda (Union-Find) con compresión de caminos y unión por rango
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool union_sets(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr)
            return false;

        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }

        return true;
    }
};

// Clase para representar el grafo
class Graph {
private:
    int V;  // número de vértices
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
    }

    void kruskalMST() {
        // Ordenar aristas por peso ascendente
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        UnionFind uf(V);
        int mst_weight = 0;

        cout << "\nAristas del Árbol de Expansión Mínima (Kruskal):\n";
        for (const Edge &e : edges) {
            if (uf.union_sets(e.u, e.v)) {
                cout << e.u << " - " << e.v << " (peso " << e.weight << ")\n";
                mst_weight += e.weight;
            }
        }

        cout << "Peso total del MST: " << mst_weight << endl;
    }
};

// Ejemplo de uso
int main() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 0, 4);
    g.addEdge(2, 0, 4);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 2, 3);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 2, 4);
    g.addEdge(4, 3, 3);
    g.addEdge(5, 2, 2);
    g.addEdge(5, 4, 3);

    g.kruskalMST();

    return 0;
}
