#include <iostream> // đồ thị vô hướng dhs bfs cây khung
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int a[105][105]; 
int vs[105];     
int n, s, t;    
struct Edge {
    int u;
    int v;
};
vector<Edge> T; 
void TreeDFS(int u) {
    vs[u] = 1; 
    for (int i = 1; i <= n; i++) {
        if (vs[i] == 0 && a[u][i] == 1) {
            Edge e;
            if (u < i) {
                e.u = u; e.v = i;
            } else {
                e.u = i; e.v = u;
            }
            T.push_back(e); 
            TreeDFS(i);     
        }
    }
}
void TreeBFS(int start) {
    queue<int> q;
    vs[start] = 1; // Danh dau dinh bat dau da duoc tham
    q.push(start); // Dua dinh bat dau vao hang doi
    
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();           
        
        for (int i = 1; i <= n; i++) {
            // Neu co canh noi tu u den i va i chua duoc tham
            if (a[u][i] == 1 && vs[i] == 0) {
                vs[i] = 1; 
                Edge e;
                // Luu dinh nho hon truoc, dinh lon hon sau
                if (u < i) {
                    e.u = u; e.v = i;
                } else {
                    e.u = i; e.v = u;
                }
                T.push_back(e); 
                q.push(i);      
            }
        }
    }
}
int main() {
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    if (!(cin >> t >> n >> s)) return 0;
    
    memset(vs, 0, sizeof(vs));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    if (t == 1) {
        TreeDFS(s);
    } else if (t == 2) {
        TreeBFS(s);
    }
    
    // Kiem tra xem co tim duoc cay khung hay khong
    if (T.size() == n - 1) {
        cout << n - 1 << "\n"; 
        for (int i = 0; i < T.size(); i++) {
            cout << T[i].u << " " << T[i].v << "\n";
        }
    } else {
        cout << 0 << "\n"; 
    }
    return 0;
}
#include <iostream> //prim
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int n, s, d;
int a[105][105];
int V[105], T[105];

struct Edge {
    int u;
    int v;
    int w;
};

vector<Edge> eT;

// So sanh de sap xep thu tu tu dien theo dinh moi duoc them vao (v)
bool cmp(Edge a, Edge b) {
    if (a.v != b.v) return a.v < b.v;
    return a.u < b.u;
}

void Prim(int start) {
    V[start] = 0; 
    T[start] = 1;
    d = 0;
    while (eT.size() < n - 1) {
        int min_w = 9999999, u = -1, v = -1;
        for (int i = 1; i <= n; i++) {
            if (T[i]) {
                for (int j = 1; j <= n; j++) {
                    if (a[i][j] < min_w && a[i][j] != 0 && a[i][j] != 10000 && T[j] == 0) {
                        min_w = a[i][j]; 
                        u = i;
                        v = j;
                    }
                }
            }
        }
        if (v == -1 || u == -1) {
            cout << 0 << endl;
            return;
        }
        T[v] = 1; 
        V[v] = 0; 
        Edge e;
        e.u = u; 
        e.v = v; 
        e.w = a[u][v];
        eT.push_back(e);
        d += a[u][v];
    }
    
    // In ra tong trong so
    cout << d << endl;
    
    for (int i = 0; i < eT.size(); i++) {
        int u = min(eT[i].u, eT[i].v);
        int v = max(eT[i].u, eT[i].v);
        cout << u << " " << v << " " << eT[i].w << endl;
    }
}

int main() {
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
	cin.tie(0) -> sync_with_stdio(0);
    if (!(cin >> n >> s)) return 0;

    // Khoi tao va doc ma tran
    for (int i = 1; i <= n; i++) {
        V[i] = 1;
        T[i] = 0; // Dam bao T duoc khoi tao
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    Prim(s);

    return 0;
}
#include <iostream> //kruskal
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc lưu thông tin một cạnh
struct Edge {
    int u, v, w;
};

// So sánh để sắp xếp cạnh theo trọng số tăng dần
bool compareEdges(Edge a, Edge b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

// Cấu trúc DSU để quản lý các tập hợp rời nhau
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Bước 1: Sắp xếp các cạnh theo trọng số
    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(n);
    vector<Edge> mst;
    int totalWeight = 0;

    // Bước 2: Duyệt qua các cạnh đã sắp xếp
    for (int i = 0; i < m; i++) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mst.push_back(edges[i]);
            totalWeight += edges[i].w;
        }
        if (mst.size() == n - 1) break;
    }

    // Kết quả
    if (mst.size() != n - 1) {
        cout << 0 << endl;
    } else {
        cout << totalWeight << endl;
        for (const auto& edge : mst) {
            cout << edge.u << " " << edge.v << " " << edge.w << endl;
        }
    }
}

int main() {
    
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    return 0;
}