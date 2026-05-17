#include <iostream> //euler 3.1
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <stack>
using namespace std;
int a[105][105] = {0};
int vs[105] = {0};
int n;

void DFS(int u) {
	vs[u] = 1;
	for (int i = 1; i <= n; i++) {
		if (a[u][i] == 1 && vs[i] == 0) {
			DFS(i);
		}
	}
}
int main() {
    ifstream cin("CT.INP");
    ofstream cout("CT.OUT");
    int option;
    cin >> option;
    if (option == 1) {
	    cin >> n;
	    for (int i = 1; i <= n; i++) {
	    	for (int j = 1; j <= n; j++) {
	    		cin >> a[i][j];
			}
		}
		// Kiem tra lien thong
		memset(vs, 0, sizeof(vs));
		DFS(1);
		int check = 1;
		for (int i = 1; i <= n; i++) if (vs[i] == 0) check = 0;
		if (check == 0) {
			cout << 0;
			return 0;
		}
		// Kiem tra Euler
		int deg[105] = {0};
		for (int i = 1; i<= n; i++) {
			for (int j = 1; j <= n; j++) {
				deg[i] += a[i][j];
			}
		}
		int countLe = 0;
		for (int i = 1; i <= n; i++) {
			if (deg[i] % 2 == 1) countLe++;
		}
		if (countLe == 0) cout << 1;
		else if (countLe == 2) cout << 2;
		else cout << 0;
	} else {
		stack<int> st, ce;
		int start;
		cin >> n >> start;
		for (int i = 1; i <= n; i++) {
	    	for (int j = 1; j <= n; j++) {
	    		cin >> a[i][j];
			}
		}
		st.push(start);
		while (st.size() != 0) {
			int s = st.top();
			int check = 0;
			for (int i = 1; i <= n; i++) {
				if (a[s][i] != 0) {
					check = 1;
					st.push(i);
					a[s][i] = a[i][s] = 0;
					break;
				}
			}
			if (check == 0) {
				st.pop();
				ce.push(s);
			}
		}
		while (ce.size() != 0) {
			cout << ce.top() << " ";
			ce.pop();
		}		
	}	
    return 0;
}
#include <iostream> //euler 3.4
#include <stack>
#include <vector>

using namespace std;

int t, n, u;
int a[105][105];
stack<int> st;
vector<int> ce;
int deg_in[105] = {0};
int deg_out[105] = {0};
int vs[105] = {0};

void DFS(int u, int b[105][105]) {
  vs[u] = 1;
  for (int i = 1; i <= n; i++) {
    if (vs[i] == 0 && b[u][i] == 1) {
      DFS(i, b);
    }
  }
}

int main() {
  // QUAN TRONG: Cau nay co 1 gia dinh la neu do thi khong lien thong (lien
  // thong yeu) thi khong la Euler hay nua Euler, phai kiem tra tinh chat nay
  // truoc
  freopen("CT.INP", "r", stdin);
  freopen("CT.OUT", "w", stdout);
  cin >> t;
  if (t == 1) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> a[i][j];
      }
    }
    // Tinh ban bac ra va ban bac vao cho moi dinh
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (a[i][j]) {
          deg_out[i]++;
          deg_in[j]++;
        }
      }
    }
    // Tao ma tran vo huong b
    int b[105][105] = {0};
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (a[i][j]) {
          b[i][j] = 1;
          b[j][i] = 1;
        }
      }
    }
    // Count in greater va count out greater dung de dem xem co bao nhieu dinh
    // co ban bac ra va ban bac vao lech nhau dung 1 don vi
    int count_in_greater = 0, count_out_greater = 0;
    bool euler = true;
    // Kiem tra lien thong yeu bang DFS
    for (int i = 1; i <= n; i++)
      vs[i] = 0;
    DFS(1, b);
    bool lien_thong = true;
    for (int i = 1; i <= n; i++) {
      if (vs[i] == 0) {
        lien_thong = false;
        break;
      }
    }
    if (!lien_thong) {
      euler = false;
      count_in_greater =
          100; // Khong phai Euler hay nua Euler do khong lien thong
    } else {
      // Kiem tra tinh chat Euler va nua Euler
      for (int i = 1; i <= n; i++) {
        if (deg_in[i] != deg_out[i]) {
          euler = false;
          if (deg_in[i] - deg_out[i] == 1)
            count_in_greater++;
          else if (deg_out[i] - deg_in[i] == 1)
            count_out_greater++;
          else {
            count_in_greater = 100; // Khong thoa man ca hai
          }
        }
      }
    }
    if (euler) {
      cout << 1 << endl; // Do thi Euler
    } else if (count_in_greater == 1 && count_out_greater == 1) {
      cout << 2 << endl; // Do thi nua Euler
    } else {
      cout << 0 << endl; // Khong la Euler hay nua Euler
    }
  }
  if (t == 2) {
    cin >> n >> u;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> a[i][j];
      }
    }
    // Tim chu trinh Euler bat dau tu u
    st.push(u);
    while (!st.empty()) {
      int current = st.top();
      bool check = false;
      // Tim canh di tiep theo
      for (int i = 1; i <= n; i++) {
        if (a[current][i]) {
          check = true;
          st.push(i);
          a[current][i] = 0; // Xoa canh da di qua
          break;
        }
      }
      // Neu khong con canh di tiep, dua vao chu trinh
      if (!check) {
        st.pop();
        ce.push_back(current);
      }
    }
    // In ra chu trinh theo thu tu dung
    for (int i = ce.size() - 1; i >= 0; i--) {
      cout << ce[i] << " ";
    }
    cout << endl;
  }

  return 0;
}
#include <iostream> //halmington
#include <vector>
#include <fstream>

using namespace std;

int a[105][105];
int vs[105];
int n, startNode, countCT = 0;
int path[105]; 

void halmington(int k) {
    if (k == n) {
    
        if (a[path[k-1]][path[0]]) {
            countCT++;
            for (int i = 0; i < n; i++) {
                printf("%d ", path[i]);
            }
            printf("%d\n", path[0]);
        }
        return;
    }

    int u = path[k-1];
    for (int v = 1; v <= n; v++) {
        if (a[u][v] && !vs[v]) {
            vs[v] = 1;
            path[k] = v;
            halmington(k + 1);
            vs[v] = 0; 
        }
    }
}

int main() {

    if (freopen("CT.INP", "r", stdin) == NULL) return 0;
    if (freopen("CT.OUT", "w", stdout) == NULL) return 0;

    if (!(cin >> n >> startNode)) return 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    path[0] = startNode;
    vs[startNode] = 1;

    halmington(1);

    if (countCT == 0) {
        printf("0\n");
    } else {
        printf("%d\n", countCT);
    }

    return 0;
}