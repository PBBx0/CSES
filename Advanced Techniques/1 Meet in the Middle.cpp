#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    unordered_map<ll, ll> cnt;
    int n, targ;
    cin >> n >> targ;
    ll a[n];
    for (ll & el : a) cin >> el;
    int k = n / 2;
    for (int mask = 0; mask < (1 << k); ++mask) {
        ll cur = 0;
        for (int i = 0; i < k; ++i) if (mask & (1 << i)) cur += a[i];
        if (cur <= targ)
            cnt[cur]++;
    }
    int m = n - k;
    ll res = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        ll cur = 0;
        for (int i = 0; i < m; ++i) if (mask & (1 << i)) cur += a[i + k];
        if (cnt.count(targ - cur))
            res += cnt[targ - cur];
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}