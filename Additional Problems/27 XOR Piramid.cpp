#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
int get_deg(int n) {
    int res = 0;
    for (int x = 2; x <= n; x <<= 1) res += n / x;
    return res;
}
bool check(int n, int k) {
    return get_deg(n) - get_deg(k) - get_deg(n - k) > 0;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & el : a) cin >> el;
    int x = 0;
    for (int i = 0; i < n; ++i) {
        if (!check(n - 1, i)) x ^= a[i];
    }
    cout << x << '\n';
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