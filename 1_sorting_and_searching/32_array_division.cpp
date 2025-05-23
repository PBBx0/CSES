#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ll lo = *max_element(all(a)) - 1, hi = 1e15;
    while (hi - lo > 1) {
        ll mid = lo + hi >> 1;
        ll cur_sum = 0;
        int cur_cnt = 1;
        for (int i = 0; i < n; ++i) {
            if (cur_sum + a[i] > mid) {
                ++cur_cnt, cur_sum = 0;
            }
            cur_sum += a[i];
        }
        (cur_cnt > k ? lo : hi) = mid;
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