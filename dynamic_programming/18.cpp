#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
#define int ll
const int MOD = 1e9 + 7;
int n, m;
vector<vector<int>> dp;
void process(int mask, int i, int val, int bs = 1) {
    dp[i + 1][(1 << n) - mask - 1] += val;
    for (int b = bs; b < n; ++b) {
        if ((mask & (1 << b)) == 0 && (mask & (1 << b - 1)) == 0)
            process(mask ^ (1 << b) ^ (1 << b - 1), i, val, b);
    }
}
void solve() {
    cin >> n >> m;
    dp.resize(m + 1, vector<int>(1 << n));
    dp[0][0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            dp[i][mask] %= MOD;
            process(mask, i, dp[i][mask]);
        }
    }
    cout << dp[m][0] % MOD << '\n';
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