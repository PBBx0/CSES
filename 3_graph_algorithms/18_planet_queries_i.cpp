#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

const int LOG = 32;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> f(n);
    for (int& el : f) {
        cin >> el;
        --el;
    }
    vector bj(LOG, vector<int>(n));
    bj[0] = f;
    for (int l = 1; l < LOG; ++l) {
        for (int v = 0; v < n; ++v) {
            bj[l][v] = bj[l - 1][bj[l - 1][v]];
        }
    }
    for (int i = 0; i < q; ++i) {
        int v, k;
        cin >> v >> k;
        --v;
        for (int l = 0; l < LOG; ++l) if ((k >> l) & 1) {
            v = bj[l][v];
        }
        cout << v + 1 << '\n';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}