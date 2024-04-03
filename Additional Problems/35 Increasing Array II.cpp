#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int & el : a) cin >> el;
    multiset<int> s{a[0]};
    ll cur_min = 0;
    for (int i = 1; i < n; ++i) {
        int x = a[i];
        s.insert(x);
        s.insert(x);
        cur_min += *s.rbegin() - x;
        s.erase(--s.end());
    }
    cout << cur_min << '\n';
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