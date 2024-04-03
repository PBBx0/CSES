#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5, M = 2e5;
struct edge {
    int a, b, c;
    edge(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
};
edge E[M];
struct DSU {
    int par[N];
    DSU(int n) {
        fill(par, par + n, -1);
    }
    int get(int v) {
        return par[v] < 0 ? v : par[v] = get(par[v]);
    }
    bool merge(int v, int u) {
        v = get(v), u = get(u);
        if (u == v) return false;
        if (par[u] < par[v]) swap(u, v);
        par[v] += par[u];
        par[u] = v;
        return true;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    int cnt = n;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        E[i] = edge(a, b, c);
    }
    sort(E, E + m, [&](auto f, auto s) {
        return f.c < s.c;
    });
    ll res = 0;
    for (int i = 0; i < m; ++i) {
        auto [a, b, c] = E[i];
        if (dsu.merge(a, b)) {
            res += c;
            cnt--;
        }
    }
    if (cnt > 1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    cout << res << '\n';
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