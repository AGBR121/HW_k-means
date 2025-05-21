#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class UnionFind {
private:
    vector<int> representative, treeHeight;

public:
    UnionFind(int n) {
        representative.resize(n);
        treeHeight.resize(n, 0);
        for (int i = 0; i < n; ++i)
            representative[i] = i;
    }

    int findRepresentative(int x) {
        if (representative[x] != x)
            representative[x] = findRepresentative(representative[x]);
        return representative[x];
    }

    bool joinSets(int x, int y) {
        int rootX = findRepresentative(x);
        int rootY = findRepresentative(y);
        if (rootX == rootY)
            return false;
        if (treeHeight[rootX] < treeHeight[rootY])
            representative[rootX] = rootY;
        else if (treeHeight[rootX] > treeHeight[rootY])
            representative[rootY] = rootX;
        else {
            representative[rootY] = rootX;
            treeHeight[rootX]++;
        }
        return true;
    }
};

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    vector<int> edgeStart;
    vector<int> edgeEnd;
    vector<int> edgeWeight;

public:
    Graph(int n) {
        adjacencyMatrix = vector<vector<int>>(n, vector<int>(n, -1));
    }

    void addEdge(int u, int v, int weight) {
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight;
    }

    void printMatrix() {
        cout << "Matriz de adyacencia ponderada:\n";
        for (const auto& row : adjacencyMatrix) {
            for (int val : row) {
                if (val == -1) cout << ". ";
                else cout << val << " ";
            }
            cout << endl;
        }
    }

    void extractEdges() {
        int n = adjacencyMatrix.size();
        edgeStart.clear();
        edgeEnd.clear();
        edgeWeight.clear();

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adjacencyMatrix[i][j] != -1) {
                    edgeStart.push_back(i);
                    edgeEnd.push_back(j);
                    edgeWeight.push_back(adjacencyMatrix[i][j]);
                }
            }
        }
    }

    void kruskalMST() {
        extractEdges();
        int n = adjacencyMatrix.size();
        int m = edgeStart.size();

        vector<int> edgeIndices(m);
        for (int i = 0; i < m; ++i) edgeIndices[i] = i;

        sort(edgeIndices.begin(), edgeIndices.end(), [&](int a, int b) {
            return edgeWeight[a] < edgeWeight[b];
        });

        UnionFind uf(n);
        int totalMSTWeight = 0;

        cout << "\nAristas del Árbol de Expansión Mínima (Kruskal):\n";
        for (int i : edgeIndices) {
            int u = edgeStart[i];
            int v = edgeEnd[i];
            int w = edgeWeight[i];

            if (uf.joinSets(u, v)) {
                cout << u << " - " << v << " (peso " << w << ")\n";
                totalMSTWeight += w;
            }
        }
        cout << "Peso total del MST: " << totalMSTWeight << endl;
    }
};

int main() {
    int numVertices = 11;
    Graph graph(numVertices);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> vertexDist(0, numVertices - 1);
    uniform_int_distribution<> weightDist(1, 100);

    for (int i = 0; i < 10; i++) {
        int u = vertexDist(gen);
        int v = vertexDist(gen);
        while (v == u) v = vertexDist(gen);
        graph.addEdge(u, v, weightDist(gen));
    }

    graph.printMatrix();
    graph.kruskalMST();

    return 0;
}
