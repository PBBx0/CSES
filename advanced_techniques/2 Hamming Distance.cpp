#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e4;
int a[N];
void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int cur = 0;
        string tmp;
        cin >> tmp;
        for (char x : tmp) cur = 2 * cur + x - '0';
        a[i] = cur;
    }
    int res = k;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            res = min(res, __builtin_popcount(a[i] ^ a[j]));
        }
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