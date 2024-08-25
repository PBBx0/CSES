#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

struct my_hash {
    size_t operator()(const int x) const {
        return x * x * 3 + x * 228 + 1337;
    }
};

void solve() {
    unordered_map<ll, ll, my_hash> cnt;
    int n, targ;
    cin >> n >> targ;
    ll a[n];
    for (ll & el : a) cin >> el;
    int k = n / 2;
    for (int mask = 0; mask < (1 << k); ++mask) {
        ll cur = 0;
        for (int i = 0; i < k; ++i) if (mask & (1 << i)) cur += a[i];
        if (cur <= targ)
            ++cnt[cur];
    }
    int m = n - k;
    ll res = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        ll cur = 0;
        for (int i = 0; i < m; ++i) if (mask & (1 << i)) cur += a[i + k];
        auto it = cnt.find(targ - cur);
        if (it != cnt.end()) res += it->second;
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
