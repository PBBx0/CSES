#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

vector<int> gen(int n) {
    if (n == 1) return {0, 1};
    auto old = gen(n - 1);
    for (int i = sz(old) - 1; i >= 0; --i) {
        old.emplace_back((1 << (n - 1)) | old[i]);
    }
    return old;
}

void println(int x, int n) {
    for (int i = 0; i < n; ++i) cout << ((x >> i) & 1);
    cout << '\n';
}

void solve() {
    int n;
    cin >> n;
    auto res = gen(n);
    for (int el : res) println(el, n);
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