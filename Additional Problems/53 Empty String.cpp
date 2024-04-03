#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
const int N = 500;
ll dp[N][N + 1], dp2[N][N + 1];
ll pow(ll a, ll pw) {
    ll res = 1;
    for (; pw > 0; pw >>= 1) {
        if (pw & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll inv(ll a) {
    return pow(a, MOD - 2);
}
ll fact[N], ifact[N];
ll C(ll n, ll k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}
void solve() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
    ifact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
    string s;
    cin >> s;
    int n = sz(s);
    if (n & 1) {
        cout << 0 << '\n';
        return;
    }
    for (int i = 0; i + 1 < n; ++i) {
        if (s[i] == s[i + 1]) dp[i][i + 2] = dp2[i][i + 2] = 1;
    }
    for (int len = 4; len <= n; len += 2) {
        for (int i = 0; i + len <= n; ++i) {
            if (s[i] == s[i + len - 1]) {
                dp[i][i + len] = dp2[i + 1][i + len - 1];
            }
            dp2[i][i + len] = dp[i][i + len];
            for (int j = i + 2; j < i + len; j += 2) {
                dp2[i][i + len] += dp[i][j] * dp2[j][i + len] % MOD * C(len / 2, (j - i) / 2);
                dp2[i][i + len] %= MOD;
            }
            dp[i][i + len] %= MOD;
        }
    }
    cout << dp2[0][n] << '\n';
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