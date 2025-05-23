#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & el : a) cin >> el;
    int x = 0;
    for (int i = 0; i < n; ++i) {
        if (i & 1) x ^= a[i];
    }
    cout << (x == 0 ? "second" : "first") << '\n';
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