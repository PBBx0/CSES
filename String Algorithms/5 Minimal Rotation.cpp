#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll N = 2e6 + 1, P = 533, MOD = 998244353;
ll pw[N], h[N];
ll get_h(int l, int r) {
    return (h[r] - h[l] * pw[r - l] % MOD + MOD) % MOD;
}
void solve() {
    string s;
    cin >> s;
    string str = s + s;
    int n = sz(s);
    pw[0] = 1;
    for (int i = 0; i < n + n; ++i) {
        pw[i + 1] = pw[i] * P % MOD;
        h[i + 1] = (h[i] * P + str[i] - 'a' + 1) % MOD;
    }
    auto cmp = [&](int a, int b) {
        int lo = 0, hi = n + 1;
        while (hi - lo > 1) {
            int md = (hi - lo) / 2 + lo;
            if (get_h(a, a + md) == get_h(b, b + md)) {
                lo = md;
            } else {
                hi = md;
            }
        }
        if (lo == n) return false;
        return str[a + lo] < str[b + lo];
    };
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (cmp(i, best)) best = i;
    }
    cout << str.substr(best, n) << '\n';
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