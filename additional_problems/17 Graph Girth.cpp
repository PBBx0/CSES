#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2500, INF = 1e9;
vector<int> g[N];
int col[N], h[N];
int res = INF;
void dfs(int v, int par, int targ) {
    col[v] = 1;
    for (int to : g[v]) if (to != par) {
        if (to == targ) {
            res = min(res, 1 + h[v]);
        }
        if (col[to]) {
            h[v] = min(h[v], h[to] + 1);
        }
    }
    for (int to : g[v]) if (to != par) {

        if (col[to] == 0) {
            h[to] = h[v] + 1;
            dfs(to, v, targ);
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    for (int v = 0; v < n; ++v) {
        fill(col, col + n, 0);
        fill(h, h + n, 0);
        dfs(v, v, v);
    }
    cout << (res == INF ? -1 : res) << '\n';
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