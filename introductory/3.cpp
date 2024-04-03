#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    string s;
    cin >> s;
    int res = 0, cur = 0, pr = -1;
    for (char el : s) {
        if (el - 'A' == pr) {
            cur++;
        } else {
            res = max(res, cur);
            cur = 1;
            pr = el - 'A';
        }
    }
    cout << max(res, cur) << '\n';
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