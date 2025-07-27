#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

const int MOD = 1e9 + 7;
int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

void solve() {
    int n;
    cin >> n;
    int res = 0;
    int cur = 1;
    for (int i = n; i >= 0; --i) {
        res = add(res, (i & 1) ? MOD - cur : cur);
        cur = mul(cur, i);
    }
    cout << res << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
