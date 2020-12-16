#include <bits/stdc++.h>
using namespace std;

const int INF = 1000;

struct routerInfo {
    vector<int> costs;
    vector<int> nextHops;

    routerInfo(int n) {
        costs = vector<int>(n, INF);
        nextHops = vector<int>(n);
        iota(nextHops.begin(), nextHops.end(), 0);
    }
};

vector<routerInfo> routers;
vector<vector<int>> costMatrix;

bool findNegativeCycle(int n, int src) {
    vector<int> distances(n, INF);
    distances[0] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                int w = costMatrix[j][k];
                if (distances[j] != INF && distances[j] + w < distances[k]) {
                    distances[k] = distances[j] + w;
                }
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            int w = costMatrix[j][k];
            if (distances[j] != INF && distances[j] + w < distances[k]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter the number of routers: ";
    cin >> n;

    costMatrix = vector<vector<int>>(n, vector<int>(n, INF));
    routers = vector<routerInfo>(n, routerInfo(n));

    cout << "Enter the cost matrix (Use 1000 for infinite / no direct link):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> costMatrix[i][j];
            if (i == j) {
                costMatrix[i][j] = 0;
            }
            routers[i].costs[j] = costMatrix[i][j];
            routers[i].nextHops[j] = j;
        }
    }

    for (int i = 0; i < n; i++) {
        if (findNegativeCycle(n, i)) {
            cout << "Negative Cycle encountered";
            return 0;
        }
    }

    bool temp;
    do {
        temp = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (routers[i].costs[j] > costMatrix[i][k] + routers[k].costs[j]) {
                        routers[i].costs[j] = routers[i].costs[k] + routers[k].costs[j];
                        routers[i].nextHops[j] = k;
                        temp = true;
                    }
                }
            }
        }
    } while (temp);

    for (int i = 0; i < n; i++) {
        cout << "\nRouting tables for router " << i + 1 << ":\n";
        cout << "Dest\tNext Hop\tCost\n";
        for (int j = 0; j < n; j++) {
            cout << j + 1 << "\t" << routers[i].nextHops[j] + 1 << "\t\t" << routers[i].costs[j] << "\n";
        }
    }
}
