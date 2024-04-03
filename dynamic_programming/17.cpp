#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
pair<ll, ll> bp[1 << 20];
void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> c(n);
    for (ll& el : c) cin >> el;
    bp[0] = {0, x};
    for (ll mask = 1; mask < (1 << n); ++mask) {
        pair<ll, ll> cur(n + 1, 0);
        for (ll b = 0; b < n; ++b) {
            ll bt = 1 << b;
            if (mask & bt) {
                auto [cnt, open] = bp[mask ^ bt];
                if (open + c[b] > x) {
                    cnt++;
                    open = 0;
                }
                open += c[b];
                cur = min(cur, make_pair(cnt, open));
            }
        }
        bp[mask] = cur;
    }
    cout << bp[(1 << n) - 1].first << '\n';
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