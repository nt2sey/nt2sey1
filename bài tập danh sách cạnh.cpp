#include <iostream> // danh sách kề -> ma trận kề (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo ma trận kề n x n với các giá trị 0
    // Đồ thị trong đề bài đánh số từ 1 đến n, nên ta dùng kích thước n+1 cho dễ quản lý
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    vector<int> deg(n + 1, 0); // Mảng lưu bậc của các đỉnh

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh (u, v)
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Vì là đồ thị vô hướng nên đánh dấu cả 2 chiều
        adj[u][v] = 1;
        adj[v][u] = 1;
        
        // Tăng bậc của cả 2 đỉnh
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
#include <iostream> // danh sách cạnh -> ma trận kề (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo ma trận kề kích thước (n + 1) x (n + 1) với các giá trị 0
    // Khởi tạo mảng quản lý bán bậc vào và bán bậc ra của từng đỉnh
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh có hướng từ u đến v
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Vì đồ thị có hướng u -> v nên chỉ gán adj[u][v] = 1
        adj[u][v] = 1;
        
        // Tăng bán bậc ra của đỉnh u và bán bậc vào của đỉnh v
        deg_out[u]++;
        deg_in[v]++;
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) của từng đỉnh
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
#include <iostream> // danh sách cạnh -> danh sách kề (bd)
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo danh sách kề dạng vector của các vector
    // Đỉnh chạy từ 1 đến n nên dùng kích thước n + 1
    vector<vector<int>> adj(n + 1);

    // Đọc m dòng tiếp theo, mỗi dòng là một cạnh (u, v)
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Đồ thị vô hướng nên lưu cả 2 chiều
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của G (bằng chính size của vector kề)
        for (int i = 1; i <= n; ++i) {
            cout << adj[i].size() << (i == n ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách kề
        cout << n << endl;

        for (int i = 1; i <= n; ++i) {
            // Sắp xếp các đỉnh kề theo thứ tự tăng dần như đề bài yêu cầu
            sort(adj[i].begin(), adj[i].end());

            // In ra số lượng đỉnh kề k
            cout << adj[i].size();

            // In ra các đỉnh kề tương ứng
            for (int j = 0; j < adj[i].size(); ++j) {
                cout << " " << adj[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách cạnh -> danh sách kề (deg)
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo danh sách kề dạng vector của các vector (từ đỉnh 1 đến n)
    vector<vector<int>> adj(n + 1);
    
    // Khởi tạo mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+)
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc m dòng tiếp theo, mỗi dòng là cung có hướng từ u đến v
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Vì đồ thị có hướng u -> v: v là đỉnh kề của u
        adj[u].push_back(v);
        
        // Tăng bán bậc ra của u và bán bậc vào của v
        deg_out[u]++;
        deg_in[v]++;
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) của các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách kề
        cout << n << endl;

        for (int i = 1; i <= n; ++i) {
            // Sắp xếp các đỉnh kề của i theo thứ tự tăng dần
            sort(adj[i].begin(), adj[i].end());

            // In ra số lượng đỉnh kề k của đỉnh i
            cout << adj[i].size();

            // In ra danh sách k số hiệu các đỉnh kề tương ứng
            for (int j = 0; j < adj[i].size(); ++j) {
                cout << " " << adj[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách cạnh -> ma trận liên thuộc (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Đọc t (loại yêu cầu), n (số đỉnh), m (số cạnh) từ danh sách cạnh
    if (!(cin >> t >> n >> m)) return 0;

    // Định nghĩa struct lưu thông tin các cạnh giống như code mẫu của bạn
    struct Edge {
        int u, v;
    };
    vector<Edge> edges;
    vector<int> deg(n + 1, 0); // Mảng để lưu bậc của từng đỉnh từ 1 đến n

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        
        // Vì đồ thị vô hướng, tăng bậc cho cả 2 đỉnh u và v
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
        // (2) Biểu diễn G dưới dạng ma trận liên thuộc
        // Dòng đầu ghi hai số tự nhiên n và m (số hàng và số cột)
        cout << n << " " << m << endl;

        // Khởi tạo ma trận liên thuộc kích thước (n + 1) x m với giá trị toàn bộ là 0
        // Dùng n + 1 để định vị các đỉnh từ 1 đến n cho thuận tiện
        vector<vector<int>> incident(n + 1, vector<int>(m, 0));

        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            // Với đồ thị vô hướng: Cạnh j nối đỉnh u và v thì cả hai đều đánh dấu là 1
            incident[u][j] = 1;
            incident[v][j] = 1;
        }

        // In ma trận liên thuộc ra file từ đỉnh 1 đến đỉnh n
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << incident[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // danh sách cạnh -> ma trận liên thuộc (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Định nghĩa cấu trúc Edge giống hệt đoạn code gốc của bạn
    struct Edge {
        int u, v;
    };
    vector<Edge> edges;

    // Mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+)
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Đọc m dòng tiếp theo từ danh sách cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});

        // Tăng bán bậc ra của đỉnh đầu u và bán bậc vào của đỉnh cuối v
        deg_out[u]++;
        deg_in[v]++;
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) các đỉnh của G
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận liên thuộc
        // Dòng đầu ghi hai số tự nhiên n và m là số hàng và số cột
        cout << n << " " << m << endl;

        // Khởi tạo ma trận liên thuộc kích thước (n + 1) x m với giá trị ban đầu là 0
        vector<vector<int>> incident(n + 1, vector<int>(m, 0));

        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            // Với đồ thị có hướng: 
            // Nút đi ra (u) đánh dấu 1, nút đi vào (v) đánh dấu -1
            incident[u][j] = 1;
            incident[v][j] = -1;
        }

        // In ma trận liên thuộc ra file từ dòng 1 đến n
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << incident[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
