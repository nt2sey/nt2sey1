#include <iostream> // đường đi BFS
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

int n, u, v;
vector<vector<int>> adj;
vector<int> vs;
vector<int> parent;
bool found = false;

// Hàm BFS dùng cho câu t = 2 để tìm đường đi từ u đến v
void BFS(int start) {
    queue<int> q;
    q.push(start);
    vs[start] = 1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == v) {
            found = true;
            return;
        }

        for (int i = 1; i <= n; ++i) {
            if (adj[curr][i] == 1 && vs[i] == 0) {
                vs[i] = 1;
                parent[i] = curr; // Lưu vết: cha của i là curr
                q.push(i);
            }
        }
    }
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");

    int t;
    // Đọc dòng đầu chứa t, dòng thứ hai chứa n, u, v
    if (!(cin >> t >> n >> u >> v)) return 0;

    // Khởi tạo ma trận kề kích thước (n + 1) x (n + 1)
    adj.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> adj[i][j];
        }
    }

    if (t == 1) {
        // (1) Tìm số lượng đường đi độ dài 2 từ u đến v
        int count_path = 0;
        // Đường đi độ dài 2 từ u -> v qua đỉnh trung gian k (u -> k -> v)
        for (int k = 1; k <= n; ++k) {
            if (adj[u][k] == 1 && adj[k][v] == 1) {
                count_path++;
            }
        }
        cout << count_path << endl;

    } else if (t == 2) {
        // (2) Tìm đường đi từ u đến v sử dụng thuật toán BFS
        vs.assign(n + 1, 0);
        parent.assign(n + 1, 0);

        BFS(u);

        if (!found) {
            // Trường hợp không có đường đi từ u đến v
            cout << 0 << endl;
        } else {
            // Truy vết ngược từ v về u bằng mảng parent
            vector<int> path;
            int curr = v;
            while (curr != 0) {
                path.push_back(curr);
                curr = parent[curr];
            }

            // In đường đi theo thứ tự từ u đến v
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i] << (i == 0 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // liên thông BFS
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <queue> // Thêm thư viện hàng đợi cho BFS

using namespace std;

int a[105][105] = {0};
int vs[105] = {0};
int n = 0;
vector<vector<int>> arr;

// Hàm BFS để tìm các đỉnh thuộc cùng một thành phần liên thông với đỉnh u
void BFS(int u) {
    queue<int> q;
    q.push(u);
    vs[u] = 1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        // Thêm đỉnh hiện tại vào thành phần liên thông đang xét
        arr.back().push_back(curr);

        for (int i = 1; i <= n; i++) {
            if (a[curr][i] == 1 && vs[i] == 0) {
                vs[i] = 1;
                q.push(i);
            }
        }
    }
}

int demTPLT() {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (vs[i] == 0) {
            vector<int> component; // Khởi tạo vector cho thành phần liên thông mới
            arr.push_back(component);
            count++;
            BFS(i); // Gọi BFS thay vì DFS
        }
    }
    memset(vs, 0, sizeof(vs));
    return count;
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");
    
    if (!(cin >> n)) return 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    int soTPLT = demTPLT();
    cout << soTPLT << "\n";
    
    for (size_t i = 0; i < arr.size(); i++) {
        // Sắp xếp các đỉnh tăng dần theo yêu cầu đề bài
        sort(arr[i].begin(), arr[i].end());
        for (size_t j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << (j == arr[i].size() - 1 ? "" : " ");
        } 
        cout << "\n";
    }

    return 0;
}
#include <iostream> // đỉnh trụ BFS
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <queue> // Thêm thư viện hàng đợi cho BFS

using namespace std;

int a[105][105];
int vs[105];
int n;

// Hàm BFS dùng để duyệt đồ thị khi loại bỏ đỉnh 'xoa'
void BFS(int start, int xoa) {
    queue<int> q;
    q.push(start);
    vs[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v <= n; v++) {
            // Có cạnh nối, đỉnh v chưa thăm và v không phải là đỉnh đang bị loại bỏ
            if (a[u][v] == 1 && !vs[v] && v != xoa) {
                vs[v] = 1;
                q.push(v);
            }
        }
    }
}

int countComponents(int xoa) {
    memset(vs, 0, sizeof(vs));
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (i != xoa && !vs[i]) {
            count++;
            BFS(i, xoa); // Gọi BFS thay vì DFS
        }
    }
    return count;
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");
    
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int temp;
            cin >> temp;
            if (temp == 1) {
                a[i][j] = a[j][i] = 1; // Chuyển thành đồ thị vô hướng
            }
        }
    }

    // 1. Đếm số thành phần liên thông ban đầu (truyền vào 0 nghĩa là không xóa đỉnh nào)
    int goc = countComponents(0);

    vector<int> dinhTru;
    
    // 2. Thử xóa từng đỉnh từ 1 đến n
    for (int i = 1; i <= n; i++) {
        int hienTai = countComponents(i);
        // Nếu số thành phần liên thông tăng lên thì i chính là đỉnh trụ
        if (hienTai > goc) {
            dinhTru.push_back(i);
        }
    }

    // 3. Xuất kết quả
    if (dinhTru.empty()) {
        cout << 0 << endl;
    } else {
        cout << dinhTru.size() << endl;
        sort(dinhTru.begin(), dinhTru.end());
        for (size_t i = 0; i < dinhTru.size(); i++) {
            cout << dinhTru[i] << (i == dinhTru.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}