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

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int binpow(int x, int pw) {
    int rs = 1;
    for (; pw > 0; pw >>= 1, x = mul(x, x)) if (pw & 1) rs = mul(rs, x);
    return rs;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (n % i != 0) continue;
        dp[i] = binpow(m, i);
        vector<int> div;
        if (i > 1) div.emplace_back(1);
        for (int t = 2; t * t <= i; ++t) {
            if (i % t != 0) continue;
            div.emplace_back(t);
            if (t * t != i) div.emplace_back(i / t);
        }
        for (int d : div) dp[i] = add(dp[i], MOD - dp[d]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (n % i != 0) continue;
        ans = add(ans, mul(dp[i], inv(i)));
    }
    cout << ans << '\n';
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
