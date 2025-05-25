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

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

void solve() {
    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int &el: a) cin >> el;
    sort(all(a));
    vector<int> dp(target + 1);
    dp[0] = 1;

    for (int d: a) {
        for (int i = d; i <= target; ++i) {
            dp[i] = add(dp[i], dp[i - d]);
        }
    }

    cout << dp[target] << '\n';
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