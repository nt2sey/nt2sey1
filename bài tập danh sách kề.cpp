#include <iostream> // danh sách kề -> ma trận kề (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh của đồ thị)
    if (!(cin >> t >> n)) return 0;

    // Khởi tạo ma trận kề n x n với các giá trị ban đầu là 0
    // Vì các đỉnh được đánh số từ 1 đến n, ta dùng kích thước n + 1 để code sạch và dễ đọc
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    vector<int> deg(n + 1, 0); // Mảng lưu bậc của các đỉnh từ 1 đến n

    // Đọc n dòng tiếp theo mô tả danh sách kề
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k; // Đọc số lượng đỉnh kề với đỉnh i
        deg[i] = k; // Bậc của đỉnh i chính bằng số lượng đỉnh kề của nó

        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v; // Đọc đỉnh v kề với đỉnh i
            adj[i][v] = 1; // Đánh dấu trên ma trận kề
        }
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg[i] << (i == n ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận kề
        // Dòng đầu ghi số tự nhiên n là bậc của ma trận kề
        cout << n << endl;

        // Trong n dòng tiếp theo, mỗi dòng ghi n số 0 hoặc 1 mô tả ma trận kề
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << adj[i][j] << (j == n ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách kề -> ma trận kề (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh của đồ thị)
    if (!(cin >> t >> n)) return 0;

    // Khởi tạo ma trận kề kích thước (n + 1) x (n + 1) với các giá trị mặc định là 0
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    
    // Khởi tạo các mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+)
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc n dòng tiếp theo mô tả danh sách kề của đồ thị có hướng
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k; // Đọc số lượng đỉnh kề đầu ra của đỉnh i
        deg_out[i] = k; // Bán bậc ra của đỉnh i chính bằng số lượng cung đi ra từ nó

        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v; // Đọc đỉnh v mà có cung đi từ i -> v
            
            adj[i][v] = 1; // Đánh dấu cung i -> v trên ma trận kề
            deg_in[v]++;   // Tăng bán bậc vào của đỉnh v lên 1 đơn vị
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận kề
        // Dòng đầu ghi số tự nhiên n là bậc của ma trận kề
        cout << n << endl;

        // Trong n dòng tiếp theo, mỗi dòng ghi n số 0 hoặc 1 mô tả ma trận kề tìm được
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << adj[i][j] << (j == n ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách kề -> danh sách cạnh (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh của đồ thị)
    if (!(cin >> t >> n)) return 0;

    // Khởi tạo cấu trúc lưu trữ danh sách cạnh tương tự form gốc của bạn
    struct Edge {
        int u, v;
    };
    vector<Edge> edges;
    vector<int> deg(n + 1, 0); // Mảng lưu bậc của từng đỉnh từ 1 đến n

    // Đọc n dòng tiếp theo mô tả danh sách kề
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        deg[i] = k; // Bậc của đỉnh i chính là số lượng đỉnh kề của nó

        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            // Vì đồ thị vô hướng, để không bị lặp lại cạnh (ví dụ 1-2 và 2-1)
            // và đảm bảo thứ tự từ điển, ta chỉ nhận các cạnh có đỉnh i < v
            if (i < v) {
                edges.push_back({i, v});
            }
        }
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg[i] << (i == n ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách cạnh
        int m = edges.size();
        // Dòng đầu ghi số tự nhiên n và m là số đỉnh và số cạnh của G
        cout << n << " " << m << endl;

        // m dòng tiếp theo, mỗi dòng ghi hai số u, v là đỉnh đầu và đỉnh cuối của cạnh
        for (int j = 0; j < m; ++j) {
            cout << edges[j].u << " " << edges[j].v << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách kề -> danh sách cạnh (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh của đồ thị)
    if (!(cin >> t >> n)) return 0;

    // Sử dụng lại cấu trúc struct Edge giống hệt đoạn code gốc của bạn
    struct Edge {
        int u, v;
    };
    vector<Edge> edges;

    // Khởi tạo các mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+) từ đỉnh 1 đến n
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc n dòng tiếp theo mô tả danh sách kề của đồ thị có hướng
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        deg_out[i] = k; // Bán bậc ra của i chính là số lượng đỉnh kề đầu ra của nó

        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v; // Có cung đi từ u -> v (ở đây u chính là i)
            
            edges.push_back({i, v});
            deg_in[v]++; // Tăng bán bậc vào của đỉnh đích v
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách cạnh
        int m = edges.size();
        // Dòng đầu ghi hai số tự nhiên n và m là số đỉnh và số cạnh của G
        cout << n << " " << m << endl;

        // Trong m dòng tiếp theo, mỗi dòng ghi hai số ui, vi là đỉnh đầu và đỉnh cuối của cạnh
        for (int j = 0; j < m; ++j) {
            cout << edges[j].u << " " << edges[j].v << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách kề -> ma trận trọng số (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo ma trận kề kích thước (n + 1) x (n + 1) với toàn bộ giá trị 0
    // Mảng lưu bậc của các đỉnh (từ đỉnh 1 đến n)
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    vector<int> deg(n + 1, 0);

    // Đọc m dòng tiếp theo mô tả danh sách cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        // Vì đồ thị vô hướng, đánh dấu đối xứng qua đường chéo chính
        adj[u][v] = 1;
        adj[v][u] = 1;

        // Tăng bậc cho cả hai đỉnh u và v
        deg[u]++;
        deg[v]++;
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg[i] << (i == n ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận kề
        cout << n << endl;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << adj[i][j] << (j == n ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách kề -> ma trận trọng số (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh của đồ thị)
    if (!(cin >> t >> n)) return 0;

    // Giữ nguyên cấu trúc struct Edge để quản lý các cạnh giống code gốc của bạn
    struct Edge {
        int u, v;
    };
    vector<Edge> edges;

    // Khởi tạo các mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+) từ đỉnh 1 đến n
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc n dòng tiếp theo mô tả danh sách kề của đồ thị có hướng
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        deg_out[i] = k; // Bán bậc ra của i bằng số lượng cung đi ra từ nó

        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v; // Có cung đi từ u -> v (với u chính là đỉnh i hiện tại)
            
            edges.push_back({i, v});
            deg_in[v]++; // Tăng bán bậc vào của đỉnh đích v
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận liên thuộc
        int m = edges.size();
        // Dòng đầu ghi ra số hàng n và số cột m của ma trận liên thuộc
        cout << n << " " << m << endl;

        // Khởi tạo ma trận liên thuộc (n + 1) hàng x m cột với giá trị mặc định là 0
        vector<vector<int>> incident(n + 1, vector<int>(m, 0));

        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            // Đồ thị có hướng: Nút đi ra (u) đánh dấu 1, nút đi vào (v) đánh dấu -1
            incident[u][j] = 1;
            incident[v][j] = -1;
        }

        // In ma trận liên thuộc ra file (từ đỉnh 1 đến n)
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << incident[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}