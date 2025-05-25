#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int INF = 1e9 + 1;

struct seg {
    int l, r, p;
};

bool operator<(seg a, seg b) {
    return a.r < b.r;
}

void solve() {
    int n;
    cin >> n;
    vector<seg> a(n);
    for (auto& [l, r, p] : a) {
        cin >> l >> r >> p;
        --l;
    }
    sort(all(a));
    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        auto [l, r, p] = a[i];
        int id = upper_bound(all(a), seg{l, l, l}) - a.begin();
        ll val = p + pref[id];
        pref[i + 1] = max(pref[i], val);
    }
    cout << pref[n] << '\n';
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