#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    sort(a.begin(), a.end());
    int res = 0, i = 0;
    for (int j = n - 1; j >= i; --j, ++res) {
        if (a[i] + a[j] <= x) {
            ++i;
        }
    }
    cout << res << '\n';
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