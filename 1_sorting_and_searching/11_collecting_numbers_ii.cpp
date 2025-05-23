#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; --a[i];
        pos[a[i]] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; ++i) ans += pos[i] < pos[i - 1];
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        std::vector<int> vals{a[l], a[r]};
        if (vals[0] > vals[1]) swap(vals[0], vals[1]);
        if (vals[0] + 1 == vals[1]) {
            ans += pos[vals[1]] < pos[vals[0]];
            ans -= pos[vals[1]] > pos[vals[0]];
        }
        for (int x : vals) {
            if (x > 0) ans -= pos[x] < pos[x - 1];
            if (x + 1 < n) ans -= pos[x + 1] < pos[x];
        }
        swap(pos[a[l]], pos[a[r]]);
        swap(a[l], a[r]);
        for (int x : vals) {
            if (x > 0) ans += pos[x] < pos[x - 1];
            if (x + 1 < n) ans += pos[x + 1] < pos[x];
        }
        cout << ans << '\n';
    }
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