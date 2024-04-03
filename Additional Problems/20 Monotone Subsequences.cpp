#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    if ((n - 1) / k + 1 > k) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    int last = 0;
    while (last != n) {
        for (int x = min(n, last + k); x > last; --x) cout << x << ' ';
        last = min(n, last + k);
    }
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
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}