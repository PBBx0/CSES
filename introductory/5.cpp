#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    if (n < 4) {
        cout << "NO SOLUTION" << '\n';
        return;
    }
    if (n == 4) {
        cout << "2 4 1 3\n";
        return;
    }
    for (int i = 0; i < (n + 1) / 2; ++i) {
        cout << i * 2 + 1 << ' ';
    }
    for (int i = 0; i < n / 2; ++i) {
        cout << i * 2 + 2 << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}