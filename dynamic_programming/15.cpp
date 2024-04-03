#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int INF = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> dp(n + 1, INF);
    dp[0] = -INF;
    for (int el : a) {
        int lo = 0, hi = n;
        while (hi - lo > 1) {
            int md = (lo + hi) / 2;
            if (dp[md] < el) {
                lo = md;
            } else {
                hi = md;
            }
        }
        dp[hi] = el;
    }
    int len = n;
    while (dp[len] == INF) --len;
    cout << len << '\n';
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