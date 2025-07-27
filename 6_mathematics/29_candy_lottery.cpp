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
using ld = long double;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<ld> dp(k + 1), dp2(k + 1);
    dp[0] = 1;
    const ld prob = 1. / k;
    for (int i = 0; i < n; ++i) {
        fill(all(dp2), 0);
        for (int old = 0; old <= k; ++old) {
            for (int nw = 1; nw <= k; ++nw) {
                dp2[max(old, nw)] += prob * dp[old];
            }
        }
        swap(dp, dp2);
    }
    ld ans = 0;
    for (int i = 0; i <= k; ++i) {
        ans += dp[i] * i;
    }
    printf("%.6Lf", ans);
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
