#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), pos(n);
    for (int& el : a) {cin >> el; el--;}
    for (int i = 0; i < n; ++i) {
        pos[a[i]] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        ans += pos[i - 1] > pos[i];
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