#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
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
const int N = 2e6 + 2;
ll fact[N], ifact[N];
ll C(ll n, ll k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}
void solve() {
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
    ifact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    for (auto & [x, y] : a) cin >> x >> y;
    sort(a.begin(), a.end(), [&](auto fst, auto snd) {
        return fst.first + fst.second < snd.first + snd.second;
    });
    a.emplace_back(n, n);
    ll dp[m + 1];
    for (int i = 0; i <= m; ++i) {
        auto [x, y] = a[i];
        dp[i] = C(x + y - 2, x - 1);
        for (int j = 0; j < i; ++j) {
            auto [x2, y2] = a[j];
            if (x2 > x || y2 > y) continue;
            dp[i] = (dp[i] - dp[j] * C(x - x2 + y - y2, x - x2) % MOD + MOD) % MOD;
        }
    }
    cout << dp[m] << '\n';
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