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
    int n, a, b;
    cin >> n >> a >> b;
    int k = 6 * n;
    const ld inv6 = 1. / 6;
    vector<ld> dp(k + 1), dp2(k + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int x = 6 * n; x >= 0; --x) {
            dp2[x] = 0;
            for (int d = 1; d <= 6 && x - d >= 0; ++d) {
                dp2[x] += inv6 * dp[x - d];
            }
        }
        swap(dp, dp2);
    }
    ld sm = 0;
    for (int i = a; i <= b; ++i) sm += dp[i];
    printf("%.6Lf\n", sm);
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
