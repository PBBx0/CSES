#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int INF = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> l(n), r(n), ev(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];
    iota(ev.begin(), ev.end(), 0);
    sort(ev.begin(), ev.end(), [&](int i, int j){
        if (r[i] != r[j]) return r[i] < r[j];
        return l[i] < l[j];
    });
    multiset<int> s;
    int ans = 0;
    for (int _ = 0; _ < k; ++_) s.insert(-INF);
    for (auto idx : ev) {
        auto it = s.upper_bound(l[idx]);
        if (it != s.begin()) {
            s.erase(--it);
            s.insert(r[idx]);
            ++ans;
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