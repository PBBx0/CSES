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

const int MOD = 1e9 + 7;

void add(int& a, int b) {
    a = a + b < MOD ? a + b : a + b - MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
    }
    vector dp(1 << n, vector<int>(n));
    dp[1 << 0][0] = 1;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int v = 0; v < n; ++v) {
            if (dp[mask][v] == 0) continue;
            for (int to : g[v]) {
                if (mask & (1 << to)) continue;
                add(dp[mask | (1 << to)][to], dp[mask][v]);
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1] << '\n';
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
