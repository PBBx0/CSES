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

const int LOG = 19;

const int MOD = 1e9 + 7;
int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int binpow(int x, int pw) {
    int rs = 1;
    for (; pw > 0; pw >>= 1, x = mul(x, x)) if (pw & 1) rs = mul(rs, x);
    return rs;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> x(1 << LOG);
    for (int el : a) ++x[el];
    for (int bit = 0; bit < LOG; ++bit) {
        for (int mask = 0; mask < (1 << LOG); ++mask) {
            if (~mask >> bit & 1) {
                x[mask] += x[mask | 1 << bit];
            }
        }
    }
    vector<ll> y(1 << LOG);
    for (int mask = 0; mask < (1 << LOG); ++mask) {
        y[mask] = binpow(2, x[mask]);
    }
    for (int bit = 0; bit < LOG; ++bit) {
        for (int mask = 0; mask < (1 << LOG); ++mask) {
            if (~mask >> bit & 1) {
                y[mask] -= y[mask | 1 << bit];
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        cout << (y[i] % MOD + MOD) % MOD << ' ';
    }
    cout << '\n';
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
