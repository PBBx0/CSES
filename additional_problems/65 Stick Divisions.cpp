#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int x, n;
    cin >> x >> n;
    int a[n];
    multiset<int> s;
    for (int & el : a) {
        cin >> el;
        s.insert(el);
    }
    ll res = 0;
    while (sz(s) >= 2) {
        int fst = *s.begin();
        s.erase(s.begin());
        int snd = *s.begin();
        s.erase(s.begin());
        s.insert(fst + snd);
        res += fst + snd;
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}