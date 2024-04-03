#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), pos(n);
    for (int& el : a) {cin >> el; el--;}
    for (int i = 0; i < n; ++i) {
        pos[a[i]] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        ans += pos[i - 1] > pos[i];
    }
    for (int i = 0; i < m; ++i) {
        int f, s;
        cin >> f >> s;
        f--, s--;
        auto [x, y] = minmax({a[f], a[s]});
        {
            if (x)
                ans -= pos[x - 1] > pos[x];
            ans -= pos[x] > pos[x + 1];
            if (y < n - 1)
                ans -= pos[y] > pos[y + 1];
            if (x + 1 != y) {
                ans -= pos[y - 1] > pos[y];
            }
        }
        swap(a[f], a[s]);
        swap(pos[x], pos[y]);
        {
            if (x)
                ans += pos[x - 1] > pos[x];
            ans += pos[x] > pos[x + 1];
            if (y < n - 1)
                ans += pos[y] > pos[y + 1];
            if (x + 1 != y) {
                ans += pos[y - 1] > pos[y];
            }
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