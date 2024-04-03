#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
ll ten[19];
void solve() {
    ll k;
    cin >> k;
    ll x = 9, cur = 1;
    while (k > x * cur) {
        k -= x * cur;
        x *= 10;
        ++cur;
    }
    ll num = ten[cur - 1] + (k - 1) / cur;
    k -= (k - 1) / cur * cur;
    string s = to_string(num);
    cout << s[k - 1] << '\n';
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
    ten[0] = 1;
    for (int i = 1; i < 19; ++i) {
        ten[i] = ten[i - 1] * 10;
    }
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}