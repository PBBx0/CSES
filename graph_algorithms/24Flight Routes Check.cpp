#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
vector<int> g[N], rg[N], vts;
int used[N];
void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) if (!used[to]) {
        dfs(to);
    }
    vts.emplace_back(v);
}
void paint_comp(int v, int c) {
    used[v] = c;
    for (int to : rg[v]) {
        if (used[to] == 1) {
            paint_comp(to, c);
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
        rg[b].emplace_back(a);
    }
    for (int v = 0; v < n; ++v) if (!used[v]) {
        dfs(v);
    }
    std::reverse(vts.begin(), vts.end());
    paint_comp(vts[0], 228);
    for (int i = 0; i < n; ++i) {
        if (used[i] != 228) {
            cout << "NO" << '\n';
            cout << i + 1 << ' ' << vts[0] + 1 << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
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