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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> indeg(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        indeg[b] += 1;
    }
    if (indeg[0] != sz(g[0]) - 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 1; i < n - 1; ++i) {
        if (indeg[i] != sz(g[i])) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<int> s{0};
    vector<int> ans;
    vector<int> ptr(n);
    while (!s.empty()) {
        int v = s.back();
        if (ptr[v] == sz(g[v])) {
            ans.emplace_back(v);
            s.pop_back();
            continue;
        }
        s.emplace_back(g[v][ptr[v]]);
        ++ptr[v];
    }
    if (sz(ans) != m + 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    reverse(all(ans));
    for (int el : ans) cout << el + 1 << ' ';
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
