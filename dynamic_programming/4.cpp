#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
constexpr int A = 1e6 + 73, MOD = 1e9 + 7;
int d[A];
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (int& el : c) cin >> el;
    d[0] = 1;
    sort(c.begin(), c.end());
    for (int el : c) {
        for (int i = 0; i + el <= x; ++i) {
            d[i + el] = (d[i + el] + d[i]) % MOD;
        }
    }
    cout << d[x] << '\n';
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