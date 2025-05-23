#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a + b == 1 || a + b > n || (a * b == 0 && a + b != 0)) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<int> f, s;
    for (int i = a + b + 1; i <= n; ++i) f.emplace_back(i), s.emplace_back(i);
    n = a + b;

    for (int i = 1; i <= a; ++i) {
        s.emplace_back(i);
        f.emplace_back(i + b);
    }
    for (int i = 1; i <= b; ++i) {
        f.emplace_back(i);
        s.emplace_back(i + a);
    }
    for (int el : f) cout << el << ' ';
    cout << '\n';
    for (int el : s) cout << el << ' ';
    cout << '\n';
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
    cin >> tt;
    while (tt--) solve();
    return 0;
}