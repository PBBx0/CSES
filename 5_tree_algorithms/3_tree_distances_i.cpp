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
vector<int> dp1, dp2, ans;

void calc_max(int v, int par) {
    dp1[v] = dp2[v] = -1;
    for (int to : g[v]) if (to != par) {
        calc_max(to, v);
        if (dp1[to] > dp1[v]) {
            dp2[v] = dp1[v];
            dp1[v] = dp1[to];
        } else if (dp1[to] > dp2[v]) {
            dp2[v] = dp1[to];
        }
    }
    ++dp1[v], ++dp2[v];
}

void dfs(int v, int par, int upper) {
    ans[v] = max(upper, dp1[v]);
    for (int to : g[v]) if (to != par) {
        dfs(to, v, max(upper, dp1[to] + 1 == dp1[v] ? dp2[v] : dp1[v]) + 1);
    }
}

void solve() {
    int n;
    cin >> n;
    g.resize(n), dp1.resize(n), dp2.resize(n), ans.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    calc_max(0, 0);
    dfs(0, 0, 0);
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
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
