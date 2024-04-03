#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    ll ans[n + 10];
    ans[1] = 0;
    ans[2] = 6;
    ans[3] = 28;
    ans[4] = 96;
    ans[5] = 252;
    ans[6] = 550;
    ans[7] = 1056;
    ans[8] = 1848;
    for (int i = 6; i <= n; ++i) {
        ans[i] = ans[i - 1] +
                1LL * (i + i - 1) * (i - 1) * (i - 1) +
                1LL * (i + i - 1) * (i + i - 2) / 2 - 2
                - 5 * 2 - 4 * 3 - (i - 5) * 2 * 4;
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}