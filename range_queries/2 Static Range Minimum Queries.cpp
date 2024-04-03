#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int LOG = 20;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> dp(n + 1);
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) dp[i] = dp[i / 2] + 1;
    vector<vector<int>> up(LOG, vector<int>(n));
    for (int i = 0; i < n; ++i) up[0][i] = a[i];
    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i + (1 << (k - 1)) < n; ++i) {
            up[k][i] = min(up[k - 1][i], up[k - 1][i + (1 << (k - 1))]);
        }
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        int k = dp[r - l];
        cout << min(up[k][l], up[k][r - (1 << k)]) << '\n';
    }
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}