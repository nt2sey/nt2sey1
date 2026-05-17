#include <iostream> //dinh tru dfs
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

int a[105][105];
int vs[105];
int n;

void DFS(int u, int xoa) {
    vs[u] = 1;
    for (int v = 1; v <= n; v++) {
        // Có cạnh, đỉnh v chưa thăm và v không phải là đỉnh đang bị loại bỏ
        if (a[u][v] == 1 && !vs[v] && v != xoa) {
            DFS(v, xoa);
        }
    }
}

int countComponents(int xoa) {
    memset(vs, 0, sizeof(vs));
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (i != xoa && !vs[i]) {
            count++;
            DFS(i, xoa);
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
                a[i][j] = a[j][i] = 1; // Chuyển thành vô hướng
            }
        }
    }

    // 1. Đếm số thành phần liên thông ban đầu
    int goc = countComponents(0);

    vector<int> dinhTru;
    
    // 2. Thử xóa từng đỉnh
    for (int i = 1; i <= n; i++) {
        int hienTai = countComponents(i);
        // Nếu số thành phần liên thông tăng lên thì i là đỉnh trụ
        if (hienTai > goc) {
            dinhTru.push_back(i);
        }
    }

    // 3. Xuất kết quả
    if (dinhTru.empty()) {
        cout << 0;
    } else {
        cout << dinhTru.size() << endl;
        sort(dinhTru.begin(), dinhTru.end());
        for (int i = 0; i < dinhTru.size(); i++) {
            cout << dinhTru[i] << " ";
        }
    }

    return 0;
}
#include <iostream> // canh cau dfs
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

int a[105][105] = {0};
int vs[105] = {0};
int n, xoaDau, xoaCuoi;

void DFS(int u) {
	vs[u] = 1;
	for (int i = 1; i <= n; i++) {
		if (a[u][i] == 1 && vs[i] == 0) {
			if ((u == xoaDau && i == xoaCuoi) || (i == xoaDau && u == xoaCuoi)) continue;
			DFS(i);
		}
	}
}

int demTPLT() {
	int count = 0;
	for (int i = 1; i <= n; i++) {
		if (vs[i] == 0) {
			count++;
			DFS(i);
		}
	}
	memset(vs, 0, sizeof(vs));
	return count;
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) {
    		cin >> a[i][j];
		}
	}
	xoaDau = 0; xoaCuoi = 0;
	int soTPLTBanDau = demTPLT();
	int countDinhTru = 0;
	vector<pair<int,int>> arr;
	for (int i = 1; i <= n; i++) {
		for (int j = i+1; j <= n; j++) {
			xoaDau = i; xoaCuoi = j;
			int soTPLT = demTPLT();
			if (soTPLT > soTPLTBanDau) {
				countDinhTru++;
				arr.push_back(make_pair(i, j));
			}
		}
	}
	cout << countDinhTru << "\n";
	if (countDinhTru != 0) {
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i].first << " " << arr[i].second << "\n";
		}
	}

    return 0;
}
#include <iostream> // đường đi dfs
#include <vector>
#include <fstream>

using namespace std;

int n, u, v;
vector<vector<int>> adj;
vector<int> vs;
vector<int> parent;
bool found = false;

// Hàm DFS dùng cho câu t = 2 để tìm đường đi từ u đến v
void DFS(int curr) {
    vs[curr] = 1;
    if (curr == v) {
        found = true;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (adj[curr][i] == 1 && vs[i] == 0) {
            parent[i] = curr; // Lưu vết: cha của i là curr
            DFS(i);
            if (found) return; // Nếu đã tìm thấy v thì dừng lại ngay lập tức
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
        // (2) Tìm đường đi từ u đến v sử dụng thuật toán DFS
        vs.assign(n + 1, 0);
        parent.assign(n + 1, 0);

        DFS(u);

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

            // In đường đi theo thứ tự xuôi dòng từ u đến v
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i] << (i == 0 ? "" : " ");
            }
            cout << endl;
        }
    }

    return 0;
}
#include <iostream> // liên thông dfs
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

int a[105][105] = {0};
int vs[105] = {0};
int n = 0;
vector<vector<int>> arr;

void DFS(int u) {
	vs[u] = 1;
	arr.back().push_back(u);
	for (int i = 1; i <= n; i++) {
		if (a[u][i] == 1 && vs[i] == 0) {
			DFS(i);
		}
	}
}

int demTPLT() {
	int count = 0;
	for (int i = 1; i <= n; i++) {
		if (vs[i] == 0) {
			vector<int> a;
			arr.push_back(a);
			count++;
			DFS(i);
		}
	}
	memset(vs, 0, sizeof(vs));
	return count;
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) {
    		cin >> a[i][j];
		}
	}
	
	
	int soTPLT = demTPLT();
	cout << soTPLT << "\n";
	for (int i = 0; i < arr.size(); i++) {
		sort(arr[i].begin(), arr[i].end());
		for (int j = 0; j < arr[i].size(); j++) {
			cout << arr[i][j] << " ";
		} 
		cout << "\n";
	}

    return 0;
}
#include<iostream> // liên thông mạnh yếu dfs
#include <cstring>
#include <fstream>

using namespace std;

int a[105][105], b[105][105];
int vs[105];
int n;

void DFS(int u, int g[105][105]) {
    vs[u] = 1;
    for (int i = 1; i <= n; i++) {
        if (g[u][i] == 1 && vs[i] == 0) {
            DFS(i, g);
        }
    }
}


int lienThongManhCheck() {
//    for (int i = 1; i <= n; i++) {
//        memset(vs, 0, sizeof(vs));
//        DFS(i, a);
//        for (int j = 1; j <= n; j++) {
//            if (vs[j] == 0) return 0;
//        }
//    }
//    return 1;

	memset(vs, 0, sizeof(vs)); 
	DFS(1, a);
	for (int j = 1; j <= n; j++) {
        if (vs[j] == 0) return 0;
    }
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= n; j++) {
    		b[i][j] = a[j][i];
		}
	}
	memset(vs, 0, sizeof(vs)); 
	DFS(1, b);
	for (int j = 1; j <= n; j++) {
        if (vs[j] == 0) return 0;
    }
    return 1;
}
int lienThongYeuCheck() {
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 1) {
                b[i][j] = 1;
                b[j][i] = 1;
            }
        }
    }

    memset(vs, 0, sizeof(vs));
    DFS(1, b); // Chỉ cần DFS từ 1 đỉnh bất kỳ (ví dụ đỉnh 1)

    for (int i = 1; i <= n; i++) {
        if (vs[i] == 0) return 0; // Có đỉnh không nằm trong khối vô hướng này
    }
    return 1;
}

int main() {
    ifstream cin("TK.INP");
    ofstream cout("TK.OUT");


    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    if (lienThongManhCheck()) {
        cout << 1;
    } else if (lienThongYeuCheck()) {
        cout << 2;
    } else {
        cout << 0;
    }

}