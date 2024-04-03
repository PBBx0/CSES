#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> l(n), r(n), ev(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        ev[i] = i;
    }
    sort(ev.begin(), ev.end(), [&](int i, int j) {
        return l[i] < l[j];
    });
    set<pair<int, int>> s;
    vector<int> out(n);
    int ans = 0;
    for (int idx : ev) {
        auto it = s.lower_bound({l[idx], 0});
        if (it == s.begin()) {
            ans++;
            out[idx] = ans;
            s.insert({r[idx], ans});
        } else {
            --it;
            int f = it->second;
            out[idx] = f;
            s.erase(it);
            s.insert({r[idx], f});
        }
    }
    cout << ans << '\n';
    for (int i = 0; i < n; ++i) cout << out[i] << ' ';
    cout << '\n';
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