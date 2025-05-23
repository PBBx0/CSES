#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

vector<pair<int, int>> history;

void gen(int n, int a, int b) {
    if (n == 1) {
        history.emplace_back(a, b);
        return;
    }
    int c = 0 ^ a ^ b;
    gen(n - 1, a, c);
    history.emplace_back(a, b);
    gen(n - 1, c, b);
}

void solve() {
    int n;
    cin >> n;
    gen(n, 1, 3);
    cout << sz(history) << '\n';
    for (auto [x, y] : history) cout << x << ' ' << y << '\n';
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