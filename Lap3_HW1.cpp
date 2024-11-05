#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

struct Point
{
    vector<double> coordinates;
    Point(initializer_list<double> coords) : coordinates(coords) {}
    Point(vector<double> coords) : coordinates(move(coords)) {} // Constructor for dynamic input
    double operator[](int index) const { return coordinates[index]; }
    int dimensions() const { return coordinates.size(); }
};

struct KDNode
{
    Point point;
    KDNode *left;
    KDNode *right;
    KDNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree
{
private:
    KDNode *root;
    int k;

    KDNode *buildTree(vector<Point> &points, int depth = 0)
    {
        if (points.empty())
            return nullptr;

        int axis = depth % k;
        sort(points.begin(), points.end(), [axis](const Point &a, const Point &b)
             { return a[axis] < b[axis]; });

        int median = points.size() / 2;
        KDNode *node = new KDNode(points[median]);

        vector<Point> leftPoints(points.begin(), points.begin() + median);
        vector<Point> rightPoints(points.begin() + median + 1, points.end());

        node->left = buildTree(leftPoints, depth + 1);
        node->right = buildTree(rightPoints, depth + 1);

        return node;
    }

    void nearestNeighbor(KDNode *node, const Point &target, KDNode *&best, double &bestDist, int depth = 0) const
    {
        if (!node)
            return;

        double dist = distance(node->point, target);
        if (dist < bestDist)
        {
            bestDist = dist;
            best = node;
        }

        int axis = depth % k;
        KDNode *nextBranch = target[axis] < node->point[axis] ? node->left : node->right;
        KDNode *otherBranch = target[axis] < node->point[axis] ? node->right : node->left;

        nearestNeighbor(nextBranch, target, best, bestDist, depth + 1);

        if (fabs(target[axis] - node->point[axis]) < bestDist)
        {
            nearestNeighbor(otherBranch, target, best, bestDist, depth + 1);
        }
    }

    double distance(const Point &a, const Point &b) const
    {
        double dist = 0.0;
        for (int i = 0; i < a.dimensions(); ++i)
        {
            dist += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(dist);
    }

public:
    KDTree(const vector<Point> &points) : root(nullptr), k(points[0].dimensions())
    {
        vector<Point> pts = points;
        root = buildTree(pts);
    }

    Point nearest(const Point &target) const
    {
        KDNode *best = nullptr;
        double bestDist = numeric_limits<double>::infinity();
        nearestNeighbor(root, target, best, bestDist);
        return best->point;
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part1\n";
    cout << "\n";
    int numPoints, dimensions;
    cout << "Enter the number of points: ";
    cin >> numPoints;
    cout << "Enter the number of dimensions: ";
    cin >> dimensions;

    vector<Point> points;
    for (int i = 0; i < numPoints; ++i)
    {
        vector<double> coords;
        cout << "Enter coordinates for point " << i + 1 << " (separated by spaces): ";
        for (int j = 0; j < dimensions; ++j)
        {
            double coordinate;
            cin >> coordinate;
            coords.push_back(coordinate);
        }
        points.emplace_back(coords);
    }

    KDTree tree(points);

    vector<double> targetCoords;
    cout << "Enter the coordinates of the target point: ";
    for (int i = 0; i < dimensions; ++i)
    {
        double coordinate;
        cin >> coordinate;
        targetCoords.push_back(coordinate);
    }
    Point target(targetCoords);

    Point nearest = tree.nearest(target);
    cout << "Nearest neighbor to (";
    for (int i = 0; i < target.dimensions(); ++i)
    {
        cout << target[i] << (i == target.dimensions() - 1 ? "" : ", ");
    }
    cout << ") is (";
    for (int i = 0; i < nearest.dimensions(); ++i)
    {
        cout << nearest[i] << (i == nearest.dimensions() - 1 ? "" : ", ");
    }
    cout << ")" << endl;
    system("pause");
    return 0;
}