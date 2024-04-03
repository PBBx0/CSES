#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
vector<int> gen(int n) {
    if (n == 1) {
        return {0, 1};
    }
    auto cur = gen(n - 1);
    auto c2 = cur;
    reverse(c2.begin(), c2.end());
    for (auto el : c2) {
        cur.emplace_back(el + (1 << (n - 1)));
    }
    return cur;
}
void solve() {
    int n;
    cin >> n;
    auto res = gen(n);
    for (auto el : res) {
        for (int i = n - 1; i >= 0; --i) {
            cout << (el & (1 << i) ? 1 : 0);
        }
        cout << '\n';
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