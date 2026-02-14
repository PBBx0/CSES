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

struct DSU {
    vector<int> t;

    DSU(int n) : t(n, -1) {}

    int get(int v) {
        return t[v] < 0 ? v : t[v] = get(t[v]);
    }

    bool unite(int v, int u) {
        v = get(v), u = get(u);
        if (u == v) return false;
        if (t[u] < t[v]) swap(u, v);
        t[v] += t[u];
        t[u] = v;
        return true;
    }
};

const int LOG = 20;
vector<vector<int>> bj, bjw;
vector<int> h;

int max_on_path(int u, int v) {
    if (h[v] < h[u]) swap(u, v);
    int len = h[v] - h[u];
    int ans = 0;
    for (int l = 0; l < LOG; ++l) {
        if (len >> l & 1) {
            ans = max(ans, bjw[l][v]);
            v = bj[l][v];
        }
    }
    if (u == v) return ans;
    for (int l = LOG - 1; l >= 0; --l) {
        if (bj[l][v] != bj[l][u]) {
            ans = max(ans, bjw[l][v]);
            ans = max(ans, bjw[l][u]);
            v = bj[l][v];
            u = bj[l][u];
        }
    }
    ans = max(ans, bjw[0][v]);
    ans = max(ans, bjw[0][u]);
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 4>> edges(m);
    int iter = 0;
    for (auto& [w, a, b, id] : edges) {
        cin >> a >> b >> w;
        --a, --b;
        id = iter++;
    }
    sort(all(edges));
    vector<int> deg(n), x(n), xw(n);
    DSU dsu(n);
    for (auto [w, a, b, id] : edges) {
        if (dsu.unite(a, b)) {
            ++deg[a], ++deg[b];
            x[a] ^= b, x[b] ^= a;
            xw[a] ^= w, xw[b] ^= w;
        }
    }
    bj.resize(LOG, vector<int>(n)), bjw.resize(LOG, vector<int>(n));
    deg[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int v = i; deg[v] == 1;) {
            int p = x[v], w = xw[v];
            bj[0][v] = p;
            bjw[0][v] = w;
            x[p] ^= v;
            xw[p] ^= w;
            --deg[v];
            --deg[p];
            v = p;
        }
    }
    for (int l = 1; l < LOG; ++l) {
        for (int v = 0; v < n; ++v) {
            bj[l][v] = bj[l - 1][bj[l - 1][v]];
            bjw[l][v] = max(bjw[l - 1][v], bjw[l - 1][bj[l - 1][v]]);
        }
    }
    h.resize(n, -1);
    h[0] = 0;
    for (int v = 0; v < n; ++v) {
        if (h[v] != -1) continue;
        int u = v, cur = 0;
        while (h[u] == -1) {
            ++cur, u = bj[0][u];
        }
        cur += h[u];
        for (u = v; h[u] == -1; u = bj[0][u]) {
            h[u] = cur--;
        }
    }
    vector<bool> ans(m);
    for (auto [w, a, b, id] : edges) {
        ans[id] = max_on_path(a, b) == w;
    }
    for (bool f : ans) {
        cout << (f ? "YES" : "NO") << '\n';
    }
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
