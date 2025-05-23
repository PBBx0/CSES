#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 5e4;
vector<int> g[N * 2], rg[N], vts;
int col[N * 2];
bitset<N> d[N];
void dfs(int v) {
    col[v] = 1;
    for (int to : g[v]) if (col[to] == 0) {
        dfs(to);
    }
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    for (int to : rg[v]) if (col[to] < N) {
        paint_comp(to, c);
    }
}
void dfs2(int v) {
    col[v] = 1;
    for (int to : g[v]) {
        if (col[to] == 0) {
            dfs2(to);
        }
        d[v - N] |= d[to - N];
    }
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    for (int i = 0; i < n; ++i) {
        if (col[i] == 0) dfs(i);
    }
    reverse(vts.begin(), vts.end());
    int c = 0;
    for (int v : vts) {
        if (col[v] < N) paint_comp(v, c + N), c++;
    }
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) if (col[v] != col[to]) {
            g[col[v]].emplace_back(col[to]);
        }
    }
    for (int v = 0; v < c; ++v) d[v].set(v);
    for (int v = N; v < N + c; ++v) {
        if (col[v] == 0) dfs2(v);
    }
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        bool ok = d[col[a] - N][col[b] - N];
        cout << (ok ? "YES" : "NO") << '\n';
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