#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
using ull = uint64_t;
const int N = 3000;
const int T = 47;
ull a[N][T];
ll count(int i, int j) {
    ll res = 0;
    for (int t = 0; t < T; ++t) {
        res += __builtin_popcountll(a[i][t] & a[j][t]);
    }
    return res;
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (ull & el : a[i]) el = 0;
        string tmp;
        cin >> tmp;
        for (int j = 0; j < sz(tmp); ++j) if (tmp[j] == '1') {
            a[i][j / 64] |= (1ULL << (j % 64));
        }
    }

    ll res = 0;
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll x = count(i, j);
            res += x * (x - 1);
        }
    }
    cout << res / 2 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}