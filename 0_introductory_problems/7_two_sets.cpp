#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    if (n % 4 == 2 || n % 4 == 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<int> first, second;
    for (; n > 1; n -= 2) {
        first.emplace_back(n);
        second.emplace_back(n - 1);
        std::swap(first, second);
    }
    if (n == 1) first.emplace_back(n);
    cout << sz(first) << '\n';
    for (int el : first) cout << el << ' ';
    cout << '\n' << sz(second) << '\n';
    for (int el : second) cout << el << ' ';
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
//    cin >> tt;
    while (tt--) solve();
    return 0;
}