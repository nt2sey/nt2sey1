#include <iostream> //ma trận trọng số -> danh sách cạnh có trọng số (bd)
#include <vector>
#include <fstream>

using namespace std;

// Cấu trúc để lưu thông tin một cạnh phục vụ cho t = 2
struct Edge {
    int u, v, w;
};

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh)
    if (!(cin >> t >> n)) return 0;

    // Khởi tạo ma trận trọng số n x n
    vector<vector<int>> c(n + 1, vector<int>(n + 1, 0));
    vector<int> deg(n + 1, 0); // Mảng lưu bậc của các đỉnh
    vector<Edge> edges;        // Danh sách các cạnh

    // Đọc ma trận trọng số
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c[i][j];
            
            // Vì là đồ thị vô hướng, ta chỉ xét một nửa ma trận (j > i) để tránh đếm trùng cạnh
            if (j > i && c[i][j] > 0 && c[i][j] <= 50) {
                // Tăng bậc của 2 đỉnh liên quan
                deg[i]++;
                deg[j]++;
                
                // Lưu cạnh vào danh sách (đã tự động sắp xếp theo thứ tự từ điển do vòng lặp i, j tăng dần)
                edges.push_back({i, j, c[i][j]});
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
        // (2) Biểu diễn G dưới dạng danh sách cạnh với trọng số
        // Dòng đầu ghi số tự nhiên n và m (số đỉnh và số cạnh)
        int m = edges.size();
        cout << n << " " << m << endl;

        // m dòng tiếp theo, mỗi dòng ghi u, v, w
        for (int i = 0; i < m; ++i) {
            cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << endl;
        }
    }

    return 0;
}
#include <iostream>//ma trận trọng số -> danh sách cạnh có trọng số (deg)
#include <vector>
#include <fstream>

using namespace std;

// Cấu trúc để lưu thông tin một cạnh phục vụ cho t = 2
struct Edge {
    int u, v, w;
};

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh)
    if (!(cin >> t >> n)) return 0;

    // Khởi tạo ma trận trọng số n x n
    vector<vector<int>> c(n + 1, vector<int>(n + 1, 0));
    
    // Mảng lưu bán bậc vào và bán bậc ra của các đỉnh
    vector<int> deg_in(n + 1, 0);  // deg-
    vector<int> deg_out(n + 1, 0); // deg+
    vector<Edge> edges;            // Danh sách các cạnh

    // Đọc ma trận trọng số
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c[i][j];
            
            // Vì là đồ thị có hướng, ta phải xét toàn bộ ma trận (bỏ điều kiện j > i)
            // Có cạnh từ i đến j khi 0 < c[i][j] <= 50
            if (c[i][j] > 0 && c[i][j] <= 50) {
                deg_out[i]++; // Tăng bán bậc ra của đỉnh đầu i
                deg_in[j]++;  // Tăng bán bậc vào của đỉnh cuối j
                
                // Lưu cạnh vào danh sách (tự động theo thứ tự từ điển do vòng lặp i, j tăng dần)
                edges.push_back({i, j, c[i][j]});
            }
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) của các đỉnh
        // Kết quả ghi ra n dòng, mỗi dòng chứa hai số tự nhiên tương ứng
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách cạnh với trọng số
        // Dòng đầu ghi số tự nhiên n và m (số đỉnh và số cạnh)
        int m = edges.size();
        cout << n << " " << m << endl;

        // m dòng tiếp theo, mỗi dòng ghi u, v, w
        for (int i = 0; i < m; ++i) {
            cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << endl;
        }
    }

    return 0;
}
#include <iostream> //danh sách cạnh vs trọng số -> ma trận trọng số (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo ma trận trọng số n x n với giá trị mặc định là 10000
    vector<vector<int>> c(n + 1, vector<int>(n + 1, 10000));
    vector<int> deg(n + 1, 0); // Mảng lưu bậc của các đỉnh

    // Quy định đường chéo chính c[i][i] = 0
    for (int i = 1; i <= n; ++i) {
        c[i][i] = 0;
    }

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh và trọng số (u, v, w)
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Gán trọng số cho cả 2 chiều vì là đồ thị vô hướng
        c[u][v] = w;
        c[v][u] = w;
        
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
        // (2) Biểu diễn G dưới dạng ma trận trọng số
        // Dòng đầu ghi số tự nhiên n là số đỉnh của G
        cout << n << endl;

        // Trong n dòng tiếp theo, mỗi dòng ghi n số mô tả ma trận trọng số
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << c[i][j] << (j == n ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> //danh sách cạnh vs trọng số -> ma trận trọng số(deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n, m;
    // Dòng đầu chứa t, dòng thứ hai chứa n (số đỉnh) và m (số cạnh)
    if (!(cin >> t >> n >> m)) return 0;

    // Khởi tạo ma trận trọng số n x n với giá trị mặc định là 10000
    vector<vector<int>> c(n + 1, vector<int>(n + 1, 10000));
    
    // Mảng lưu bán bậc vào (deg-) và bán bậc ra (deg+) của các đỉnh
    vector<int> deg_in(n + 1, 0);
    vector<int> deg_out(n + 1, 0);

    // Quy định đường chéo chính c[i][i] = 0
    for (int i = 1; i <= n; ++i) {
        c[i][i] = 0;
    }

    // Đọc m dòng tiếp theo, mỗi dòng chứa một cạnh có hướng (u, v, w)
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Vì là đồ thị có hướng nên CHỈ gán một chiều từ u đến v
        c[u][v] = w;
        
        // Cập nhật bán bậc ra cho đỉnh đầu u và bán bậc vào cho đỉnh cuối v
        deg_out[u]++;
        deg_in[v]++;
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+) của các đỉnh
        // Kết quả ghi ra n dòng
        for (int i = 1; i <= n; ++i) {
            cout << deg_in[i] << " " << deg_out[i] << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận trọng số
        // Dòng đầu ghi số tự nhiên n là số đỉnh của G
        cout << n << endl;

        // Trong n dòng tiếp theo, mỗi dòng ghi n số mô tả ma trận trọng số
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << c[i][j] << (j == n ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}