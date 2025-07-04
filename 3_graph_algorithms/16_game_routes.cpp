#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

vector<vector<int>> g;
vector<int> dp;

int dfs(int v) {
    if (dp[v] != -1) return dp[v];
    dp[v] = 0;
    for (int to : g[v]) {
        dp[v] = add(dp[v], dfs(to));
    }
    return dp[v];
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    dp.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    dp[n - 1] = 1;
    cout << dfs(0) << '\n';
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