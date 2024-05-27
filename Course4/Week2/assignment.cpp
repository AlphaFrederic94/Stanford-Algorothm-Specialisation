#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>
#include <ctime>

using namespace std;

#define axis pair<double, double>
#define C 25
#define T (1 << C)
#define FINISH ((1 << C) - 1)

// Function to calculate the TSP using dynamic programming with bitmasking
double TSP(int mask, int position, vector<vector<double> > &distance, vector<vector<double> > &visited) {
    if (mask == FINISH) return distance[position][0];
    if (visited[mask][position] != -1) return visited[mask][position];

    double minValue = DBL_MAX;

    for (int i = 0; i < C; ++i) {
        if (!(mask & (1 << i))) {
            double result = distance[position][i] + TSP(mask | (1 << i), i, distance, visited);
            minValue = min(minValue, result);
        }
    }

    return visited[mask][position] = minValue;
}

int main() {
    clock_t start, end;
    start = clock();

    int number;
    double x, y;
    vector<axis> city(C);
    vector<vector<double> > distance(C, vector<double>(C, 0));
    vector<vector<double> > visited(T, vector<double>(C, -1));

    ifstream file("tsp.txt");

    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    file >> number;

    for (int i = 0; i < C; ++i) {
        file >> x >> y;
        city[i] = axis(x, y);
    }

    file.close();

    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
            if (i != j) {
                distance[i][j] = sqrt(pow(city[i].first - city[j].first, 2) + pow(city[i].second - city[j].second, 2));
            }
        }
    }

    double result = TSP(1, 0, distance, visited);
    cout << floor(result) << endl;

    end = clock();
    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    cout << setprecision(2) << fixed << duration << 's' << endl;

    return 0;
}

