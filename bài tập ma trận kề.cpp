#include <iostream> //ma trận kề -> liên thuộc (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+)
        for (int i = 0; i < n; ++i) {
            int deg_in = 0;
            int deg_out = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) deg_out++; // Bán bậc ra: tổng hàng i
                if (adj[j][i] == 1) deg_in++;  // Bán bậc vào: tổng cột i
            }
            cout << deg_in << " " << deg_out << endl;
        }
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận liên thuộc
        struct Edge {
            int u, v;
        };
        vector<Edge> edges;

        // Tìm các cạnh theo thứ tự từ điển (u, v)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    edges.push_back({i, j});
                }
            }
        }

        int m = edges.size();
        cout << n << " " << m << endl;

        // Khởi tạo ma trận liên thuộc n hàng x m cột với giá trị 0
        vector<vector<int>> incident(n, vector<int>(m, 0));

        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            // Với đồ thị có hướng: 
            // Nút đi ra (u) đánh dấu 1, nút đi vào (v) đánh dấu -1
            incident[u][j] = 1;
            incident[v][j] = -1;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << incident[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // ma trận kề -> liên thuộc (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của đồ thị vô hướng G
        for (int i = 0; i < n; ++i) {
            int deg = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    deg++;
                }
            }
            cout << deg << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng ma trận liên thuộc
        struct Edge {
            int u, v;
        };
        vector<Edge> edges;

        // Tìm danh sách các cạnh duy nhất theo thứ tự từ điển (j > i)
        // Đỉnh lưu ở đây vẫn là chỉ số 0-indexed để tiện dựng ma trận liên thuộc sau đó
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) { 
                if (adj[i][j] == 1) {
                    edges.push_back({i, j});
                }
            }
        }

        int m = edges.size();
        // Dòng đầu ghi ra hai số tự nhiên n và m là số hàng và số cột
        cout << n << " " << m << endl;

        // Khởi tạo ma trận liên thuộc kích thước n hàng x m cột, ban đầu toàn số 0
        vector<vector<int>> incident(n, vector<int>(m, 0));

        // Điền số 1 vào ma trận liên thuộc dựa trên danh sách cạnh thu được
        for (int j = 0; j < m; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            incident[u][j] = 1; // Cạnh j đi qua đỉnh u
            incident[v][j] = 1; // Cạnh j đi qua đỉnh v
        }

        // In ma trận liên thuộc ra file kết quả
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << incident[i][j] << (j == m - 1 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // ma trận kề -> danh sách cạnh (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    // Đọc ma trận kề
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+)
        for (int i = 0; i < n; ++i) {
            int deg_in = 0;
            int deg_out = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) deg_out++; // Tổng hàng i là bán bậc ra
                if (adj[j][i] == 1) deg_in++;  // Tổng cột i là bán bậc vào
            }
            cout << deg_in << " " << deg_out << endl;
        }
    } 
    else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách cạnh
        struct Edge {
            int u, v;
        };
        vector<Edge> edges;

        // Duyệt tìm các cạnh theo thứ tự từ điển (u, v)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    // Lưu đỉnh theo chỉ số 1-based (cộng thêm 1)
                    edges.push_back({i + 1, j + 1});
                }
            }
        }

        int m = edges.size();
        // Dòng đầu in số đỉnh n và số cạnh m
        cout << n << " " << m << endl;

        // In danh sách các cạnh
        for (int i = 0; i < m; ++i) {
            cout << edges[i].u << " " << edges[i].v << endl;
        }
    }

    return 0;
}
#include <iostream> // ma trận kề -> danh sách cạnh (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của đồ thị vô hướng G
        // Do đồ thị vô hướng nên bậc của đỉnh i chính là tổng số lượng số 1 trên hàng i
        for (int i = 0; i < n; ++i) {
            int deg = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    deg++;
                }
            }
            cout << deg << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách cạnh
        struct Edge {
            int u, v;
        };
        vector<Edge> edges;

        // Vì đồ thị vô hướng, cạnh (i, j) và (j, i) là một.
        // Để tránh trùng lặp và đảm bảo thứ tự từ điển, ta chỉ xét nửa trên ma trận (j > i)
        // Đề bài dùng đỉnh bắt đầu từ 1, nên lúc lưu ta sẽ lưu (i + 1, j + 1)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) { 
                if (adj[i][j] == 1) {
                    edges.push_back({i + 1, j + 1});
                }
            }
        }

        int m = edges.size();
        cout << n << " " << m << endl;

        // In ra danh sách các cạnh
        for (int j = 0; j < m; ++j) {
            cout << edges[j].u << " " << edges[j].v << endl;
        }
    }

    return 0;
}
#include <iostream> //ma trận kề-> danh sách kề (deg)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    // Đọc ma trận kề từ tệp tin
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bán bậc vào (deg-) và bán bậc ra (deg+)
        for (int i = 0; i < n; ++i) {
            int deg_in = 0;
            int deg_out = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) deg_out++; // Bán bậc ra: tổng trên hàng i
                if (adj[j][i] == 1) deg_in++;  // Bán bậc vào: tổng trên cột i
            }
            cout << deg_in << " " << deg_out << endl;
        }
    } 
    else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách kề
        // Dòng đầu tiên ghi số đỉnh n
        cout << n << endl;

        for (int i = 0; i < n; ++i) {
            vector<int> neighbors;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    // Đỉnh kề được đánh số từ 1 đến n
                    neighbors.push_back(j + 1);
                }
            }

            // Ghi số lượng đỉnh kề k và danh sách các đỉnh kề
            cout << neighbors.size();
            for (int v : neighbors) {
                cout << " " << v;
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // ma trận kề -> danh sách kề (bd)
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream cin("DT.INP");
    ofstream cout("DT.OUT");

    int t, n;
    if (!(cin >> t >> n)) return 0;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Xác định bậc các đỉnh của đồ thị vô hướng G
        for (int i = 0; i < n; ++i) {
            int deg = 0;
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    deg++;
                }
            }
            cout << deg << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    } else if (t == 2) {
        // (2) Biểu diễn G dưới dạng danh sách kề
        // Dòng đầu tiên ghi ra số tự nhiên n là số đỉnh của G
        cout << n << endl;

        // Xét từng đỉnh từ 0 đến n-1 (tương ứng với đỉnh 1 đến n)
        for (int i = 0; i < n; ++i) {
            vector<int> neighbors; // Lưu danh sách các đỉnh kề với i
            
            // Duyệt qua tất cả các đỉnh j để tìm đỉnh kề.
            // Do ma trận kề duyệt j từ 0 đến n-1 nên thứ tự đỉnh kề đã tự động tăng dần.
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] == 1) {
                    neighbors.push_back(j + 1); // Đỉnh trong file xuất phát từ 1
                }
            }

            // Số lượng đỉnh kề k
            int k = neighbors.size();
            cout << k;

            // In các đỉnh kề phía sau
            for (int j = 0; j < k; ++j) {
                cout << " " << neighbors[j];
            }
            cout << endl;
        }
    }

    return 0;
}