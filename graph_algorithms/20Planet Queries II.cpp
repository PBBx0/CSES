#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

const int N = 2e5, LOG = 20;
int nx[LOG][N], col[N], pos[N], comp[N], h[N], sz[N + 1];

int count_h(int v) {
    if (h[v] != -1) return h[v];
    if (col[v] == 2) return h[v] = 0;
    return h[v] = count_h(nx[0][v]) + 1;
}
int get(int v, int k) {
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) v = nx[i][v];
    }
    return v;
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> nx[0][i];
        nx[0][i]--;
    }

    for (int i = 1; i < LOG; ++i)
        for (int v = 0; v < n; ++v)
            nx[i][v] = nx[i - 1][nx[i - 1][v]];


    int c = 0;
    for (int v = 0; v < n; ++v) if (col[v] == 0) {
        int t = v;
        for (; col[t] == 0; t = nx[0][t]) {
            col[t] = 3;
        }
        if (col[t] == 3) {
            col[t] = 2;
            comp[t] = ++c;
            pos[t] = sz[c]++;
            for (int y = nx[0][t]; y != t; y = nx[0][y]) {
                col[y] = 2;
                comp[y] = c;
                pos[y] = sz[c]++;
            }
        }
        for (int y = v; col[y] == 3; y = nx[0][y]) {
            col[y] = 1;
            comp[y] = c;
        }
    }
    fill(h, h + n, -1);
    for (int v = 0; v < n; ++v) if (h[v] == -1) {
        count_h(v);
    }


    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (h[a] >= h[b]) {
            int cur = h[a] - h[b];
            a = get(a, cur);
            if (a == b) {
                cout << cur << '\n';
                continue;
            }
            if (col[a] == 2 && col[b] == 2 && comp[a] == comp[b]) {
                int cmp = comp[a];
                cout << cur + (pos[b] - pos[a] + sz[cmp]) % sz[cmp] << '\n';
                continue;
            }
        }
        cout << -1 << '\n';
    }
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}