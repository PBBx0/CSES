#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

ll ans = 0;

struct DSU {
    vector<int> dsu;

    DSU(int n) : dsu(n, -1) {}

    int get(int v) {
        return dsu[v] < 0 ? v : dsu[v] = get(dsu[v]);
    }

    void unite(int u, int v, ll x) {
        u = get(u), v = get(v);
        if (u == v) return;
        ans += x * dsu[u] * dsu[v];
        if (dsu[u] < dsu[v]) swap(u, v);
        dsu[v] += dsu[u];
        dsu[u] = v;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<tuple<ll, int, int>> edges(n - 1);
    for (auto& [x, a, b] : edges) {
        cin >> a >> b >> x;
        --a, --b;
    }
    sort(rall(edges));
    DSU dsu(n);
    for (auto [x, a, b] : edges) {
        dsu.unite(a, b, x);
    }
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
