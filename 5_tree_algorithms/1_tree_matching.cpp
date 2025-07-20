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
vector<array<int, 2>> dp;

void dfs(int v, int par) {
    int sm = 0;
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
        sm += max(dp[to][0], dp[to][1]);
    }
    dp[v][0] = dp[v][1] = sm;
    for (int to : g[v]) if (to != par) {
        dp[v][0] = max(dp[v][0], sm - max(dp[to][0], dp[to][1]) + dp[to][1] + 1);
    }
}

void solve() {
    int n;
    cin >> n;
    g.resize(n);
    dp.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    cout << max(dp[0][0], dp[0][1]) << '\n';
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
