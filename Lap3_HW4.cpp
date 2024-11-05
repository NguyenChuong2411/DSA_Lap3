#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Data structure for a point with features and an optional label
struct Point
{
    vector<double> features;
    string label;
};

// Function to calculate Euclidean distance between two points
double euclideanDistance(const Point &p1, const Point &p2)
{
    double sum = 0.0;
    for (size_t i = 0; i < p1.features.size(); ++i)
    {
        sum += (p1.features[i] - p2.features[i]) * (p1.features[i] - p2.features[i]);
    }
    return sqrt(sum);
}

// KNN worker function that processes a subset of the dataset
void knnWorker(const vector<Point> &dataset, const Point &target, int k, int start, int end, vector<Point> &partialNeighbors)
{
    vector<pair<double, Point>> distances;

    for (int i = start; i < end; ++i)
    {
        double dist = euclideanDistance(dataset[i], target);
        distances.push_back({dist, dataset[i]});
    }

    // Sort distances to get the k-nearest neighbors for this subset
    sort(distances.begin(), distances.end(), [](const pair<double, Point> &a, const pair<double, Point> &b)
         { return a.first < b.first; });

    for (int i = 0; i < k && i < distances.size(); ++i)
    {
        partialNeighbors.push_back(distances[i].second);
    }
}

// Main KNN function that simulates a multi-threaded environment
vector<Point> knnSearch(const vector<Point> &dataset, const Point &target, int k, int numThreads)
{
    vector<Point> neighbors;
    int chunkSize = dataset.size() / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? dataset.size() : (i + 1) * chunkSize;

        vector<Point> partialNeighbors;
        knnWorker(dataset, target, k, start, end, partialNeighbors);

        // Combine partial results
        neighbors.insert(neighbors.end(), partialNeighbors.begin(), partialNeighbors.end());
    }

    // Sort the combined results to get the closest k neighbors
    sort(neighbors.begin(), neighbors.end(), [&](const Point &a, const Point &b)
         { return euclideanDistance(a, target) < euclideanDistance(b, target); });

    if (neighbors.size() > k)
    {
        neighbors.resize(k);
    }
    return neighbors;
}

// Main function
int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part4\n";
    cout << "\n";
    vector<Point> dataset = {
        {{17.99, 10.38, 122.80, 1001.0, 0.1184, 0.2776, 0.3001, 0.1471, 0.2419, 0.0787}, "M"},
        {{20.57, 17.77, 132.90, 1326.0, 0.0847, 0.0786, 0.0869, 0.0702, 0.1812, 0.0567}, "M"},
        {{19.69, 21.25, 130.00, 1203.0, 0.1096, 0.1599, 0.1974, 0.1279, 0.2069, 0.0599}, "M"},
        {{11.42, 20.38, 77.58, 386.1, 0.1425, 0.2839, 0.2414, 0.1052, 0.2597, 0.0974}, "M"},
        {{20.29, 14.34, 135.10, 1297.0, 0.1003, 0.1328, 0.1980, 0.1043, 0.1809, 0.0588}, "M"}
        // Continue adding data points as necessary
    };

    int k = 3;          // Number of neighbors
    int numThreads = 2; // Simulated number of threads

    // Define a target point to search for its k-nearest neighbors
    Point target = {{15.0, 15.0, 100.0, 500.0, 0.1, 0.1, 0.1, 0.1, 0.1, 0.05}, ""};

    // Perform KNN search
    vector<Point> neighbors = knnSearch(dataset, target, k, numThreads);

    // Display neighbors
    cout << "K-Nearest Neighbors:" << endl;
    for (const auto &neighbor : neighbors)
    {
        cout << "Label: " << neighbor.label << " Features: ";
        for (const auto &feature : neighbor.features)
        {
            cout << feature << " ";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
