#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e6, MOD = 1e9 + 7;
int cnt[N];
void solve() {
    int n;
    cin >> n;
    int x = n * (n + 1) / 2;
    if (x & 1) {
        cout << 0 << '\n';
        return;
    }
    x >>= 1;
    cnt[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = x - i; j >= 0; --j) {
            cnt[i + j] = (cnt[i + j] + cnt[j]) % MOD;
        }
    }
    ll res = cnt[x];
    if (res & 1) res += MOD;
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}