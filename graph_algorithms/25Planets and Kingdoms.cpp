#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], rg[N], vts;
int col[N];
void dfs(int v) {
    col[v] = 0;
    for (auto to : g[v]) if (col[to] == -1) {
        dfs(to);
    }
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    col[v] = c;
    for (int to : rg[v]) if (!col[to]) {
        paint_comp(to, c);
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    fill(col, col + n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    for (int v = 0; v < n; ++v) if (col[v] == -1) {
        dfs(v);
    }
    reverse(vts.begin(), vts.end());
    int c = 0;
    for (int v : vts) if (!col[v]) {
        paint_comp(v, ++c);
    }
    cout << c << '\n';
    for (int i = 0; i < n; ++i) cout << col[i] << ' ';
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