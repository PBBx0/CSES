#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    int d[k];
    for (int & el : d) cin >> el;
    bool dp[n + 1];
    dp[0] = false;
    string out;
    for (int i = 1; i <= n; ++i) {
        dp[i] = false;
        for (int x : d) {
            if (i >= x) dp[i] |= !dp[i - x];
        }
        out += dp[i] ? 'W' : 'L';
    }
    cout << out << '\n';
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