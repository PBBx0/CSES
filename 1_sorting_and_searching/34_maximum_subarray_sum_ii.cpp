#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const ll INF = 1e18;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> p(n + 1);
    multiset<ll> vals;
    ll ans = -INF;
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
        if (i + 1 - l >= 0) {
            vals.emplace(p[i + 1 - l]);
        }
        if (i - r >= 0) {
            vals.erase(vals.find(p[i - r]));
        }
        if (!vals.empty()) {
            ans = max(ans, p[i + 1] - *vals.begin());
        }
    }
    cout << ans << '\n';
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