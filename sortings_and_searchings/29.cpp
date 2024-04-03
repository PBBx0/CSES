#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), p(n + 1);
    for (auto& el : a) cin >> el;
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }
    unordered_map<ll, ll> cnt;
    ll res = 0;
    for (auto el : p) {
        res += cnt[(el % n + n) % n];
        cnt[(el % n + n) % n]++;
    }
    cout << res << '\n';
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