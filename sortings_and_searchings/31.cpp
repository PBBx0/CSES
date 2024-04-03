#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    ll lo = 0, hi = 1e15;
    for (int& el : a) {
        cin >> el;
        lo = max(lo, (ll)el - 1);
    }
    while (hi - lo > 1) {
        ll md = lo + hi >> 1;
        ll cur = 0, cnt = 1;
        for (auto el : a) {
            cur += el;
            if (cur > md) {
                cur = el;
                cnt++;
            }
        }
        if (cnt <= k) {
            hi = md;
        } else {
            lo = md;
        }
    }
    cout << hi << '\n';
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