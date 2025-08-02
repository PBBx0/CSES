#ifndef LOCAL
#pragma GCC optimize("O3")
#endif

#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

const ll INF = 1e18;

void solve() {
    ll mm, pm, mp, pp;
    mm = pm = mp = pp = -INF;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        mm = max(mm, -x - y);
        pp = max(pp, x + y);
        mp = max(mp, -x + y);
        pm = max(pm, x - y);
        cout << max(pp + mm, pm + mp) << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
