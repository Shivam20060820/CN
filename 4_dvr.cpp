#include <iostream>
using namespace std;

int main() {
    int n, cost[10][10], dist[10][10], i, j, k;

    cout << "Enter number of routers: ";
    cin >> n;

    cout << "Enter cost matrix (use 999 for no link):\n";
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            cin >> cost[i][j];
            dist[i][j] = cost[i][j];
        }

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    cout << "\nShortest distance between routers:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            if (dist[i][j] >= 999)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        cout << endl;
    }

    return 0;
}