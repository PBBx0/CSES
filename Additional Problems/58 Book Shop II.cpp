#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int A = 1e5;
int dp[A + 1];
void solve() {
    int n, x;
    cin >> n >> x;
    int cost[n], pages[n], cnt[n];
    for (int & el : cost) cin >> el;
    for (int & el : pages) cin >> el;
    for (int & el : cnt) cin >> el;
    auto relax = [&](int cur, int p) {
        for (int j = x - cur; j >= 0; --j) {
            dp[j + cur] = max(dp[j + cur], dp[j] + p);
        }
    };
    for (int i = 0; i < n; ++i) {
        int cur = cnt[i];
        for (int t = 1; t <= cur; t <<= 1) {
            relax(t * cost[i], t * pages[i]);
            cur -= t;
        }
        if (cur) relax(cur * cost[i], cur * pages[i]);
    }
    int res = *max_element(dp, dp + x + 1);
    cout << res << '\n';
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