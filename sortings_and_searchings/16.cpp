#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    vector<int> pr(n), nx(n);
    for (int i = 0; i < n; ++i) {
        pr[i] = (n + i - 1) % n;
        nx[i] = (i + 1) % n;
    }
    for (int cur = 1, cnt = 0; cnt < n; ++cnt) {
        cout << cur + 1 << ' ';
        nx[pr[cur]] = nx[cur];
        pr[nx[cur]] = pr[cur];
        cur = nx[nx[cur]];
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