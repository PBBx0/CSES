#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
using ll = int64_t;
const ll T = 19, D = 10;
void solve() {
    pair<ll, ll> dp[D][D][T][D];
    ll ones[T];
    ones[0] = ones[1] = 0;
    for (int i = 2; i < T; ++i) ones[i] = 10 * (ones[i - 1] + 1);
    for (int a = 1; a < D; ++a) {
        for (int d = 0; d < D; ++d) {
            for (int x = 0; x < D; ++x) {
                if (x >= max(a,  d)) continue;
                //dp[a][d][0][x]
                ll dig = 10 + x - max(a, d), cnt = 1;
                if (dig != 0 && dig >= max(d, a - 1)) {
                    dig = 0, cnt++;
                }
                if (a != 1) {
                    cnt += dp[a - 1][d][0][dig].second;
                    dig = dp[a - 1][d][0][dig].first;
                }
                dp[a][d][0][x] = {dig, cnt};
            }
        }
    }
    for (int l = 1; l < T; ++l) {
        for (int a = 1; a < D; ++a) {
            for (int d = 0; d < D; ++d) {
                for (int x = 0; x < D; ++x) {
                    if (x >= max(a,  d)) continue;
                    //dp[a][d][l][x]
                    ll dig = 10 + x - max(a, d), cnt = 1;
                    if (dig == 9) dig = 0, cnt++;
                    cnt += ones[l];
                    cnt += dp[9][max(d, a - 1)][l - 1][dig].second;
                    dig = dp[9][max(d, a - 1)][l - 1][dig].first;
                    if (dig != 0 && dig >= max(d, a - 1)) {
                        dig = 0, cnt++;
                    }
                    if (a != 1) {
                        cnt += dp[a - 1][d][l][dig].second;
                        dig = dp[a - 1][d][l][dig].first;
                    }
                    dp[a][d][l][x] = {dig, cnt};
                }
            }
        }
    }
    string n;
    cin >> n;
    int s = sz(n);
    ll ans = 0;
    for (int l = 0; l <= s - 2; ++l) {
        int j = s - l - 2;
        int a = n[j] - '0';
        if (a == 0) continue;
        int d = 0;
        for (int i = 0; i < j; ++i) d = max(d, n[i] - '0');
        int x = n[s - 1] - '0';
        if (x >= max(a, d)) x = 0, ans++;
        auto [dig, cnt] = dp[a][d][l][x];
        ans += cnt;
        n[s - 1] = char('0' + dig);
        n[j] = '0';
    }
    if (n[s - 1] != '0') ans++, n[s - 1] = '0';
    cout << ans << '\n';
}

signed main() {
    int tt = 1;
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
//    cin >> tt;
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    while (tt--) solve();
    return 0;
}
