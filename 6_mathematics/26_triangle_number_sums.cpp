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

bool is_triangle(ll x) {
    ll y = sqrt(x * 2);
    for (ll t = y - 3; t <= y + 3; ++t) if (y * (y + 1) == 2 * x) return true;
    return false;
}

void solve() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        ll n;
        cin >> n;
        bool ok = false;
        if (is_triangle(n)) {
            cout << 1 << '\n';
            ok = true;
            continue;
        }
        for (ll j = 1, s = 1; s < n; ++j, s += j) {
            if (is_triangle(n - s)) {
                cout << 2 << '\n';
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << 3 << '\n';
        }
    }
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
