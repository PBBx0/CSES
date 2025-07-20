#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

ll ask(int l, int r) {
    cout << l + 1 << ' ' << r << endl;
    ll res;
    cin >> res;
    if (res == 0) exit(EXIT_SUCCESS);
    return res;
}

void solve() {
    int n;
    cin >> n;
    ll cnt = ask(0, n);
    for (int len = 1; len < n; ++len) {
        ll cnt2 = ask(0, len + 1);
        ll p = (cnt2 - cnt - len * (len - 3) / 2) / 2;
        if (len != 1) {
            cnt = ask(1, len + 1);
        }
        if (p != 0) {
            cnt = ask(0, p + 1);
            cnt = ask(0, p);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
