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

const int LOG = 20;
vector<vector<int>> g;
vector<int> bj[LOG], h;

void dfs(int v, int par) {
    bj[0][v] = par;
    for (int to : g[v]) if (to != par) {
            h[to] = h[v] + 1;
            dfs(to, v);
        }
}

int get_anc(int v, int k) {
    for (int l = 0; l < LOG; ++l) {
        if (k & (1 << l)) v = bj[l][v];
    }
    return v;
}

int lca(int a, int b) {
    if (h[a] < h[b]) swap(a, b);
    a = get_anc(a, h[a] - h[b]);
    if (a == b) return a;
    for (int l = LOG - 1; l >= 0; --l) {
        if (bj[l][a] != bj[l][b]) {
            a = bj[l][a];
            b = bj[l][b];
        }
    }
    return bj[0][a];
}


void solve() {
    int n, q;
    cin >> n >> q;
    g.resize(n);
    h.resize(n);
    for (auto& el : bj) el.resize(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        --p;
        g[i].emplace_back(p);
        g[p].emplace_back(i);
    }
    dfs(0, 0);
    for (int l = 1; l < LOG; ++l) {
        for (int v = 0; v < n; ++v) {
            bj[l][v] = bj[l - 1][bj[l - 1][v]];
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << lca(a, b) + 1 << '\n';
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
