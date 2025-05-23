#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ll lo = 0, hi = 2e18;
    while (hi - lo > 1) {
        ll mid = lo + hi >> 1;
        ll cnt = 0;
        for (int x : a) {
            cnt += mid / x;
            if (cnt >= t) break;
        }
        (cnt >= t ? hi : lo) = mid;
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