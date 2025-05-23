#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& el : a) cin >> el;
    sort(a.begin(), a.end());
    ll sum = accumulate(a.begin(), a.end(), 0LL);
    ll res = sum;
    for (ll mask = 0; mask < (1 << n); ++mask) {
        ll s1 = 0;
        for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
            s1 += a[i];
        }
        res = min(res, abs(sum - s1 - s1));
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