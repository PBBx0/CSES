#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5, INF = 1e9 + 1000 - 7;
vector<int> g[N], rg[N], g2[N], vts;
int col[N], sz[N], sz2[N], sz3[N];
void dfs(int v) {
    col[v] = -1;
    for (int to : g[v]) if (col[to] == -2) dfs(to);
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    sz[c]++;
    for (int to : rg[v]) if (col[to] == -1) paint_comp(to, c);
}
void dfs2(int v, int c) {
    col[v] = INF;
    sz2[c] += sz[v];
    sz3[c] += sz[v] * (sz[v] != 1) + 1;
    for (int to : g2[v]) if (col[to] != INF) dfs2(to, c);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    fill(col, col + n, -2);
    int c = 0;
    for (int v = 0; v < n; ++v) if (col[v] == -2) dfs(v);
    reverse(vts.begin(), vts.end());
    for (int v : vts) if (col[v] == -1) paint_comp(v, c++);
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) {
            g2[col[v]].emplace_back(col[to]);
            g2[col[to]].emplace_back(col[v]);
        }
    }
    int ans = 0, c2 = 0;
    for (int v = 0; v < c; ++v) {
        if (col[v] != INF) {
            dfs2(v, c2);
            ans += min(sz2[c2], sz3[c2] - 1);
            c2++;
        }
    }
    cout << ans << '\n';
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