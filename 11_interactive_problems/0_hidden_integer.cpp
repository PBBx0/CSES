#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
using ll = int64_t;

bool ask(int x) {
    cout << "? " << x << endl;
    string ans;
    cin >> ans;
    return ans == "YES";
}

void solve() {
    int lo = 0, hi = 1e9;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        (ask(mid) ? lo : hi) = mid;
    }
    cout << "! " << hi << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
