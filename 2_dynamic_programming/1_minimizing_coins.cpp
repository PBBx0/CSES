#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int INF = 1e9 + 7;

void solve() {
    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    sort(all(a));
    vector<int> dp(target + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= target; ++i) {
        for (int d : a) {
            if (i - d < 0) break;
            dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }
    cout << (dp[target] == INF ? -1 : dp[target]) << '\n';
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