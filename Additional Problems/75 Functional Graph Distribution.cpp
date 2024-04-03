#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;
using ll = int64_t;

const ll MOD = 1e9 + 7;
const int N = 5005;

ll fact[N], ifact[N], pw[N], s[N][N];

ll inv(ll x) {
    ll res = 1;
    for (ll p = MOD - 2; p > 0; p >>= 1) {
        if (p & 1) res = res * x % MOD;
        x = x * x % MOD;
    }
    return res;
}

ll CC(ll n, ll k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve() {
    fact[0] = 1;
    for (ll i = 1; i < N; ++i) fact[i] = i * fact[i - 1] % MOD;
    ifact[N - 1] = inv(fact[N - 1]);
    for (ll i = N - 1; i > 0; --i) ifact[i - 1] = ifact[i] * i % MOD;

    s[0][0] = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            s[i][j] = (1LL * (i - 1) * s[i - 1][j] % MOD + s[i - 1][j - 1]) % MOD;
        }
    }

    int n;
    cin >> n;
    pw[0] = 1;
    for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * n % MOD;
    for (int k = 1; k <= n; ++k) {
        ll rs = 0;
        for (int cnt = k; cnt <= n; ++cnt) {
//            TFAE
//            ll fst = CC(n, cnt), snd = s[cnt][k], trd = cnt * pw[max(0, n - cnt - 1)] % MOD;
//            (rs += fst * snd % MOD * trd % MOD) %= MOD;
            (rs += CC(n - 1, cnt - 1) * s[cnt][k] % MOD * pw[n - cnt] % MOD) %= MOD;
        }
        cout << rs << '\n';
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
    solve();
    return 0;
}