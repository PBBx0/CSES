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

vector<vector<int>> g;
vector<int> c, ans;

set<int> dfs(int v, int par) {
    set<int> res;
    res.emplace(c[v]);
    for (int to : g[v]) if (to != par) {
        auto s = dfs(to, v);
        if (sz(s) > sz(res)) swap(s, res);
        for (int el : s) res.emplace(el);
    }
    ans[v] = sz(res);
    return res;
}

void solve() {
    int n;
    cin >> n;
    g.resize(n), c.resize(n), ans.resize(n);
    for (int& el : c) cin >> el;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    for (int el : ans) cout << el << ' ';
    cout << '\n';
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
