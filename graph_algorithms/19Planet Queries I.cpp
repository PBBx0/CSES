#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5, LOG = 30;
int nx[LOG][N];
int get(int v, int k) {
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) {
            v = nx[i][v];
        }
    }
    return v;
}
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> nx[0][i];
        nx[0][i]--;
    }
    for (int i = 1; i < LOG; ++i) {
        for (int v = 0; v < n; ++v) {
            nx[i][v] = nx[i - 1][nx[i - 1][v]];
        }
    }
    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        x--;
        cout << get(x, k) + 1 << '\n';
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