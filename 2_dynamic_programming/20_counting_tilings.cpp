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

int n, m;
vector<vector<int>> dp;

void process(int j, int mask, int to_add, int bit) {
    dp[j + 1][((1 << n) - 1) ^ mask] = add(dp[j + 1][((1 << n) - 1) ^ mask], to_add);
    for (int i = bit; i + 1 < n; ++i) {
        if ((mask & (3 << i)) == 0) {
            process(j, mask ^ (3 << i), to_add, i + 2);
        }
    }
}

void solve() {
    cin >> n >> m;
    dp.resize(m + 1, vector<int>(1 << n));
    dp[0][0] = 1;
    for (int j = 0; j < m; ++j) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            process(j, mask, dp[j][mask], 0);
        }
    }
    cout << dp[m][0] << '\n';
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