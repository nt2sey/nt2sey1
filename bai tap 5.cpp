#include <iostream> //dijkstra
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int a[105][105], d[105], truoc[105], vs[105];
int n, s, t;

int main() {
    freopen("DN.INP", "r", stdin);
    freopen("DN.OUT", "w", stdout);

    if (!(cin >> n >> s >> t)) return 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        d[i] = 20000;
        vs[i] = 0;
        truoc[i] = 0;
    }
    d[s] = 0;

    while (true) {
        int u = 0;
        int min_d = 20000;

        for (int i = 1; i <= n; i++) {
            if (!vs[i] && d[i] < min_d) {
                min_d = d[i];
                u = i;
            }
        }

        if (u == 0 || u == t) break;

        vs[u] = 1;

        for (int i = 1; i <= n; i++) {
            if (!vs[i] && a[u][i] < 10000) {
                if (d[i] > d[u] + a[u][i]) {
                    d[i] = d[u] + a[u][i];
                    truoc[i] = u;
                }
            }
        }
    }

    if (d[t] >= 10000) {
        cout << 0;
    } else {
        cout << d[t] << endl;
        vector<int> duongDi;
        int curr = t;
        while (curr != 0) {
            duongDi.push_back(curr);
            curr = truoc[curr];
            if (curr == s) {
                duongDi.push_back(s);
                break;
            }
        }
        reverse(duongDi.begin(), duongDi.end());
        for (int i = 0; i < duongDi.size(); i++) {
            cout << duongDi[i] << (i == duongDi.size() - 1 ? "" : " ");
        }
    }

    return 0;
}


#include <iostream> //bellman
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int a[105][105], d[105], truoc[105], vs[105];
int n, s, t;

int main() {
    freopen("BN.INP", "r", stdin);
    freopen("BN.OUT", "w", stdout);



    if (!(cin >> n >> s >> t)) return 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        d[i] = 10000;
        truoc[i] = s;

    }
    d[s] = 0;
    int k = 1;

    while (k <= n-1) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i] > d[j] + a[j][i]) {
                    d[i] = d[j] + a[j][i];
                    truoc[i] = j;
                }
            }
        }
        k++;
    }

    int checkChuTrinhAm = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i] > d[j] + a[j][i]) {
                checkChuTrinhAm = 1;
            }
        }
    }
    if (checkChuTrinhAm == 1) cout << -1;
    else if (d[t] == 10000) cout << 0;
    else {
        cout << d[t] << endl;
        vector<int> duongDi;
        int curr = t;
        while (curr != 0) {
            duongDi.push_back(curr);
            curr = truoc[curr];
            if (curr == s) {
                duongDi.push_back(s);
                break;
            }
        }
        reverse(duongDi.begin(), duongDi.end());
        for (int i = 0; i < duongDi.size(); i++) {
            cout << duongDi[i] << (i == duongDi.size() - 1 ? "" : " ");
        }
    }

    return 0;
}

#include <iostream> //floyd
#include <vector>

using namespace std;

int a[105][105], Next[105][105], d[105][105];
int n;

int main() {

    freopen("DN.INP", "r", stdin);
    freopen("DN.OUT", "w", stdout);
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            d[i][j] = a[i][j];
            if (i != j && a[i][j] < 10000)
                Next[i][j] = j;
            else
                Next[i][j] = -1;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
    int u = -1, v = -1, max_val = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && d[i][j] > max_val && d[i][j] < 10000) {
                max_val = d[i][j];
                u = i; v = j;
            }
        }
    }
    if (u != -1) {
        cout << u << " " << v << " " << d[u][v] << endl;
        while (u != -1) {
            cout << u << " ";
            if (u == v) break;
            u = Next[u][v];
        }
    }

    return 0;
}