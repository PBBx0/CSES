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



template <typename... Args>
int add(Args... args) {
    int res = 0;
    return ((res = res + args < MOD ? res + args : res + args - MOD), ...);
}

template <typename... Args>
int mul(Args... args) {
    ll res = 1;
    return ((res = res * args % MOD), ...);
}

int binpow(int x, ll pw) {
    int rs = 1;
    for (; pw > 0; pw >>= 1, x = mul(x, x)) if (pw & 1) rs = mul(rs, x);
    return rs;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}

void solve() {
    ll n;
    cin >> n;
    int s1 = binpow(2, n * n);
    int s2 = binpow(2, (n * n + 1) / 2);
    int s3 = binpow(2, n % 2 == 1 ?  (n - 1) * (n - 1) / 4 + (n + 1) / 2 + 1 : n * n / 4 + 1);
    cout << mul(inv(4), add(s1, s2, s3)) << '\n';
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
