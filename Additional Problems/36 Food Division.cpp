#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    int cur[n], need[n];
    for (int & el : cur) cin >> el;
    for (int & el : need) cin >> el;
    for (int i = 0; i < n; ++i) cur[i] -= need[i];
    int addend[n + 1];
    fill(addend, addend + n + 1, 0);
    auto add = [&](int l, int r, int x) {
        addend[l] += x;
        addend[r] -= x;
    };
    set<pair<int, int>> fst, snd;
    for (int i = 0; i < n; ++i) {
        if (cur[i] > 0) fst.emplace(i, cur[i]);
        if (cur[i] < 0) snd.emplace(i, -cur[i]);
    }
    while (!fst.empty()) {
        auto [p1, x1] = *fst.begin();
        fst.erase(fst.begin());
        auto [p2, x2] = *snd.begin();
        snd.erase(snd.begin());
        int c = min(x1, x2);
        add(p1, p2, c);
        x1 -= c, x2 -= c;
        if (x1) fst.emplace(p1, x1);
        if (x2) snd.emplace(p2, x2);
    }
    int a[n];
    a[0] = addend[0];
    for (int i = 1; i < n; ++i) a[i] = a[i - 1] + addend[i];
    sort(a, a + n);
    ll res = 0, x = a[n >> 1];
    for (int y : a) res += abs(y - x);
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