#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
void solve() {
    ll n, k;
    cin >> n >> k;
    set<ll> s;
    for (int i = 0; i < n; ++i) s.insert(i);
    for (int i = 0; i < n; ++i) {
        if (n - i - 1 <= k) {
            k -= (n - i - 1);
            cout << *s.rbegin() + 1 << ' ';
            s.erase(--s.end());
        } else if (k == 0) {
            cout << *s.begin() + 1 << ' ';
            s.erase(s.begin());
        } else {
            cout << k + 1 << ' ';
            s.erase(k);
            k = 0;
        }
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}