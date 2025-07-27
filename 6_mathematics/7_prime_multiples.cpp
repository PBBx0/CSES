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

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> p(k);
    for (ll& el : p) cin >> el;
    ll res = 0;
    for (ll mask = 0; mask < (1 << k); ++mask) {
        int cnt = 0;
        ll cur = n;
        for (int i = 0; i < k; ++i) {
            if (mask >> i & 1) {
                cnt++;
                cur /= p[i];
            }
        }
        if (cnt & 1) cur = -cur;
        res += cur;
    }
    cout << n - res << '\n';
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
