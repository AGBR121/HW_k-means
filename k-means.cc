#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Point
{
public:
    vector<double> attributes;
    int clusterIndex;

    Point(const vector<double> &attr) : attributes(attr), clusterIndex(-1) {}
};

class KMeans
{
private:
    int numClusters;
    int maxIterations;
    vector<vector<double>> centroidList;

    double euclideanDistance(const vector<double> &a, const vector<double> &b)
    {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); ++i)
            sum += pow(a[i] - b[i], 2);
        return sqrt(sum);
    }

    void assignToNearestCentroid(vector<Point> &points)
    {
        for (auto &point : points)
        {
            double minDistance = numeric_limits<double>::max();
            int closestCluster = -1;
            for (int i = 0; i < numClusters; ++i)
            {
                double dist = euclideanDistance(point.attributes, centroidList[i]);
                if (dist < minDistance)
                {
                    minDistance = dist;
                    closestCluster = i;
                }
            }
            point.clusterIndex = closestCluster;
        }
    }

    void recalculateCentroids(vector<Point> &points)
    {
        vector<vector<double>> newCentroids(numClusters, vector<double>(points[0].attributes.size(), 0.0));
        vector<int> clusterSizes(numClusters, 0);

        for (const auto &point : points)
        {
            for (size_t j = 0; j < point.attributes.size(); ++j)
                newCentroids[point.clusterIndex][j] += point.attributes[j];
            clusterSizes[point.clusterIndex]++;
        }

        for (int i = 0; i < numClusters; ++i)
        {
            if (clusterSizes[i] == 0)
                continue;
            for (size_t j = 0; j < newCentroids[i].size(); ++j)
                newCentroids[i][j] /= clusterSizes[i];
        }

        centroidList = newCentroids;
    }

public:
    KMeans(int numClusters, int maxIterations)
        : numClusters(numClusters), maxIterations(maxIterations) {}

    void train(vector<Point> &points)
    {
        centroidList.clear();
        srand(time(0));
        for (int i = 0; i < numClusters; ++i)
        {
            int index = rand() % points.size();
            centroidList.push_back(points[index].attributes);
        }

        for (int iter = 0; iter < maxIterations; ++iter)
        {
            assignToNearestCentroid(points);
            recalculateCentroids(points);
        }
    }

    void displayResults(const vector<Point> &points)
    {
        vector<int> clusterCounts(numClusters, 0);

        for (const auto &point : points)
        {
            clusterCounts[point.clusterIndex]++;
            cout << "Clúster " << point.clusterIndex << ": ";
            for (double val : point.attributes)
                cout << val << " ";
            cout << endl;
        }

        cout << "\n--- Resumen por Clúster ---\n";
        for (int i = 0; i < numClusters; ++i)
        {
            cout << "Clúster " << i << ": " << clusterCounts[i] << " elementos\n";
        }

        cout << "\n--- Centroides Finales ---\n";
        for (int i = 0; i < numClusters; ++i)
        {
            cout << "Clúster " << i << " centroide: ";
            for (double val : centroidList[i])
                cout << val << " ";
            cout << endl;
        }
    }
};

vector<Point> loadDataset(const string &filename)
{
    ifstream file(filename);
    string line;
    vector<Point> dataset;

    bool headerSkipped = false;

    while (getline(file, line))
    {
        if (!headerSkipped)
        {
            headerSkipped = true;
            continue;
        }

        stringstream ss(line);
        string cell;
        vector<double> attributes;
        int col = 0;

        while (getline(ss, cell, '\t'))
        {
            if (col == 4 || (col >= 9 && col <= 14))
            {
                try
                {
                    double val = cell.empty() ? 0.0 : stod(cell);
                    attributes.push_back(val);
                }
                catch (...)
                {
                    attributes.push_back(0.0); // fallback for non-numeric or missing values
                }
            }
            col++;
        }

        if (!attributes.empty())
        {
            dataset.emplace_back(attributes);
        }
    }

    return dataset;
}

int main()
{
    vector<Point> dataset = loadDataset("kmeans.txt");
    if (dataset.empty())
    {
        cerr << "No se cargaron datos. Verifica el archivo.\n";
        return 1;
    }

    KMeans model(3, 100);
    model.train(dataset);
    model.displayResults(dataset);

    return 0;
}