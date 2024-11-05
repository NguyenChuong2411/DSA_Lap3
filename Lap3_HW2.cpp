#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct Point
{
    double x, y;
};

// Function to calculate the distance between two points
double distance(const Point &p1, const Point &p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute-force method for finding the closest pair in a small subset
double bruteForceClosest(Point points[], int left, int right)
{
    double minDist = numeric_limits<double>::max();
    for (int i = left; i < right; ++i)
        for (int j = i + 1; j < right; ++j)
            minDist = min(minDist, distance(points[i], points[j]));
    return minDist;
}

// Helper function to find the minimum distance in the "strip" of points
double stripClosest(Point strip[], int size, double delta)
{
    double minDist = delta;
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j)
            minDist = min(minDist, distance(strip[i], strip[j]));
    return minDist;
}

// Recursive function for closest pair of points
double closestPairRec(Point points[], int left, int right)
{
    if (right - left <= 3)
        return bruteForceClosest(points, left, right);

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = closestPairRec(points, left, mid);
    double dr = closestPairRec(points, mid, right);

    double delta = min(dl, dr);

    Point strip[right - left];
    int j = 0;
    for (int i = left; i < right; i++)
        if (abs(points[i].x - midPoint.x) < delta)
            strip[j++] = points[i];

    return min(delta, stripClosest(strip, j, delta));
}

// Closest pair of points function
double closestPair(Point points[], int n)
{
    sort(points, points + n, [](const Point &p1, const Point &p2)
         { return p1.x < p2.x; });
    return closestPairRec(points, 0, n);
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework_Lap3_Part2\n";
    cout << "\n";
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    Point *points = new Point[n];
    cout << "Enter the coordinates of each point (x y):" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    double minDist = closestPair(points, n);
    cout << "The smallest distance between two points is: " << minDist << endl;

    delete[] points;
    system("pause");
    return 0;
}
