#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    ll t = 1LL * n * (n + 1) / 2;
    if (t & 1) {
        cout << "NO" << '\n';
        return;
    }
    set<int> s1, s2, s;
    ll sm1 = 0, sm2 = 0;
    for (int i = 1; i <= n; ++i) {
        s.insert(i);
    }
    while (!s.empty()) {
        int el = *s.rbegin();
        s.erase(el);
        if (sm1 < sm2) {
            sm1 += el;
            s1.insert(el);
        } else {
            sm2 += el;
            s2.insert(el);
        }
    }
    if (sm1 != sm2) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    cout << sz(s1) << '\n';
    for (auto el : s1) cout << el << ' ';
    cout << '\n' << sz(s2) << '\n';
    for (auto el : s2) cout << el << ' ';
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
    while (tt--) solve();
    return 0;
}