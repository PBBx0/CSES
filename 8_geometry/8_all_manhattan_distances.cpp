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
using lll = __int128;

void solve() {
    int n;
    cin >> n;
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    sort(all(x));
    sort(all(y));
    lll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += x[i] * (i - (n - i - 1));
        sum += y[i] * (i - (n - i - 1));
    }
    lll INF = 1e18;
    ll first = sum / INF;
    ll second = sum % INF;
    if (first) {
        cout << first;
        auto s = to_string(second);
        for (int i = sz(s); i < 18; ++i) cout << 0;
    }
    cout << second << '\n';

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
