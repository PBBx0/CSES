#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<int> par(n, -1);
    par[0] = -2;
    deque<int> q{0};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int to : g[v]) {
            if (par[to] != -1) continue;
            par[to] = v;
            q.emplace_back(to);
        }
    }
    if (par[n - 1] == -1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<int> path;
    for (int v = n - 1; v != -2; v = par[v]) {
        path.emplace_back(v);
    }
    reverse(all(path));
    cout << sz(path) << '\n';
    for (int el : path) cout << el + 1 << ' ';
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