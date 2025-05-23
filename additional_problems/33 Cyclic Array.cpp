#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int LOG = 18, N = 2e5;
int pos[LOG][N + N];
void solve() {
    int n;
    ll k;
    cin >> n >> k;
    int n2 = n + n;
    ll a[n2];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    int r = 0;
    ll sum = 0;
    for (int i = 0; i < n2; ++i) {
        while (r < n2 && sum + a[r] <= k) sum += a[r++];
        pos[0][i] = r;
        sum -= a[i];
    }
    for (int i = 1; i < LOG; ++i) {
        for (int j = 0; j < n2; ++j) {
            pos[i][j] = pos[i - 1][j] == n2 ? n2 : pos[i - 1][pos[i - 1][j]];
        }
    }
    auto get = [&](int l) {
        int res = 1;
        int v = l;
        for (int i = LOG - 1; i >= 0; --i) {
            if (pos[i][v] < l + n) {
                res += 1 << i;
                v = pos[i][v];
            }
        }
        return res;
    };
    int res = n;
    for (int i = 0; i < n; ++i) res = min(res, get(i));
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
    solve();
    return 0;
}