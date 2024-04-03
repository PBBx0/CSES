#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N];
int par[N], used[N];
int vtx = -1, prnt = -1;
void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) if (to != par[v]) {
        if (used[to] == 0) {
            par[to] = v;
            dfs(to);
        } else if (used[to] == 1) {
            vtx = v, prnt = to;
        }
    }
    used[v] = 2;
}
void solve() {
    fill(par, par + N, -1);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    for (int v = 0; v < n; ++v) if (used[v] == 0) {
        dfs(v);
    }
    if (vtx == -1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vector<int> vts{prnt};
    for (int t = vtx; t != prnt; t = par[t]) {
        vts.emplace_back(t);
    }
    vts.emplace_back(prnt);
    cout << sz(vts) << '\n';
    for (auto el : vts) cout << el + 1 << ' ';
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}