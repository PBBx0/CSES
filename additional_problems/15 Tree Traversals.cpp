#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5;
int a[N], b[N], pos[N];
void process(int la, int ra, int lb, int rb) {
    if (la == ra && lb == rb) return;
    int root = a[la];
    int len = pos[root] - lb;
    process(la + 1, la + 1 + len, lb, lb + len);
    process(la + 1 + len, ra, pos[root] + 1, rb);
    cout << root + 1 << ' ';
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        pos[--b[i]] = i;
    }
    process(0, n, 0, n);
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