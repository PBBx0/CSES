#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
int ask(int n, int k) {
    if (n % 2 == 0) {
        if (k < n / 2) {
            return k * 2 + 1;
        }
        return 2 * ask(n / 2, k - n / 2);
    } else {
        if (k < n / 2) {
            return k * 2 + 1;
        }
        if (k == n / 2) {
            return 0;
        }
        return 2 * ask(n / 2, k - n / 2 - 1) + 2;
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    cout << ask(n, k - 1) + 1 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt;
    cin >> tt;
    while (tt--) solve();
    return 0;
}