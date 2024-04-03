#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
int col[N], par[N];
vector<int> g[N];
int vtx = -1, prnt = -1;
void dfs(int v) {
    col[v] = 1;
    for (auto to : g[v]) {
        if (col[to] == 1) {
            vtx = v, prnt = to;
        }
        if (col[to] == 0) {
            par[to] = v;
            dfs(to);
        }
    }
    col[v] = 2;
}
void solve() {
    int n, m;
    cin >> n >> m;
    fill(par, par + n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
    }
    for (int v = 0; v < n; ++v) if (col[v] == 0) {
        dfs(v);
    }
    if (vtx == -1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    vector<int> out{prnt};
    for (int v = vtx; v != prnt; v = par[v]) {
        out.emplace_back(v);
    }
    out.emplace_back(prnt);
    reverse(out.begin(), out.end());
    cout << sz(out) << '\n';
    for (int el : out) cout << el + 1 << ' ';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}