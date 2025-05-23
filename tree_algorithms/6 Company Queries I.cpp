#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5, LOG = 19;
int up[LOG][N];
int get(int v, int k) {
    for (int i = 0; i < LOG && v != -2; ++i) {
        if (k & (1 << i)) v = up[i][v];
    }
    return v;
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        cin >> up[0][i];
        up[0][i]--;
    }
    up[0][0] = -2;
    for (int i = 1; i < LOG; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][v] == -2 ? -2 : up[i - 1][up[i - 1][v]];
        }
    }
    for (int i = 0; i < q; ++i) {
        int v, k;
        cin >> v >> k;
        cout << get(--v, k) + 1 << '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}