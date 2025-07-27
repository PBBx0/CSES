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

const int T = 2e6 + 1;

int fact[T], ifact[T];

void solve() {
    fact[0] = 1;
    for (int i = 1; i < T; ++i) {
        fact[i] = mul(i, fact[i - 1]);
    }
    ifact[T - 1] = inv(fact[T - 1]);
    for (int i = T - 1; i > 0; --i) {
        ifact[i - 1] = mul(i, ifact[i]);
    }
    int n, m;
    cin >> n >> m;
    cout << mul(fact[n + m - 1], mul(ifact[n - 1], ifact[m])) << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
