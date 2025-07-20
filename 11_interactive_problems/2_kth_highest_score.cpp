#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

const int INF = 1e9 + 7;

int ask(int country, int i) {
    if (i == 0) return INF;
    cout << "FS"[country] << " " << i << endl;
    int x;
    cin >> x;
    return x;
}

void solve() {
    int n, k;
    cin >> n >> k;
    int lo = max(0, k - n);
    int hi = min(k, n) + 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        int x = ask(0, mid);
        int y = ask(1, k - mid);
        (x > y ? lo : hi) = mid;
    }
    int x = ask(0, lo);
    int y = ask(1, k - lo);
    int ans = min(x, y);
    if (lo < n && k - lo > 0) {
        x = ask(0, lo + 1);
        y = ask(1, k - lo - 1);
        ans = max(ans, min(x, y));
    }
    cout << "! " << ans << '\n';
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
