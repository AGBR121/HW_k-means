#include <iostream>
#include <vector>
#include <limits>
#include <random>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adjMatrix;

public:
    Graph(int numNodes)
    {
        adjMatrix = vector<vector<int>>(numNodes, vector<int>(numNodes, -1));
    }

    void add_edge(int from, int to, int weight)
    {
        if (from == to)
            return; // evitar bucles
        adjMatrix[from][to] = weight;
        adjMatrix[to][from] = weight;
    }

    bool has_edge(int from, int to)
    {
        return adjMatrix[from][to] != -1;
    }

    void print()
    {
        cout << "Matriz de adyacencia ponderada:\n";
        int numNodes = adjMatrix.size();
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                if (adjMatrix[i][j] == -1)
                    cout << ". ";
                else
                    cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void prim()
    {
        int numNodes = adjMatrix.size();
        vector<int> mstParent(numNodes, -1);
        vector<int> minWeight(numNodes, numeric_limits<int>::max());
        vector<bool> included(numNodes, false);

        minWeight[0] = 0;

        for (int step = 0; step < numNodes - 1; ++step)
        {
            int u = -1;
            int currentMin = numeric_limits<int>::max();
            for (int node = 0; node < numNodes; ++node)
            {
                if (!included[node] && minWeight[node] < currentMin)
                {
                    currentMin = minWeight[node];
                    u = node;
                }
            }

            if (u == -1)
                break;

            included[u] = true;

            for (int v = 0; v < numNodes; ++v)
            {
                if (adjMatrix[u][v] != -1 && !included[v] && adjMatrix[u][v] < minWeight[v])
                {
                    minWeight[v] = adjMatrix[u][v];
                    mstParent[v] = u;
                }
            }
        }

        cout << "\nAristas del Árbol de Expansión Mínima (Prim):\n";
        int totalWeight = 0;
        for (int node = 1; node < numNodes; ++node)
        {
            if (mstParent[node] != -1)
            {
                cout << mstParent[node] << " - " << node << " (peso " << adjMatrix[node][mstParent[node]] << ")\n";
                totalWeight += adjMatrix[node][mstParent[node]];
            }
        }
        cout << "Peso total del MST: " << totalWeight << endl;
    }
};

int main()
{
    int numNodes = 11;
    Graph graph(numNodes);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nodeDist(0, numNodes - 1);
    uniform_int_distribution<> weightDist(1, 20);

    int edgesAdded = 0;
    while (edgesAdded < 20)
    {
        int from = nodeDist(gen);
        int to = nodeDist(gen);
        int weight = weightDist(gen);
        if (from != to && !graph.has_edge(from, to))
        {
            graph.add_edge(from, to, weight);
            edgesAdded++;
        }
    }

    graph.print();
    graph.prim();

    return 0;
}
