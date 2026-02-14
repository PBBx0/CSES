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

ll my_solve(ll n, ll m) {
    --n, --m;
    ll cnt = lcm(n, m);
    ll g = gcd(n, m);
    ll g2 = 2 * g;
    ll dos = ((n) / g2) * ((m) / g2);
    ll tres = ((n - g) / g2) * ((m - g) / g2);
    return cnt - dos - tres + 1;
}

void kek() {
    const ll T = 30;
    ll col[T][T];
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            col[i][j] = 0;
        }
    }
    ll iter = 0;
    for (ll n = 2; n <= T; ++n) {
        for (ll m = 2; m <= T; ++m) {
            ++iter;
            int i = 0, j = 0, di = 1, dj = 1;
            ll cur = 1;
            col[0][0] = iter;
            while (true) {
                i += di, j += dj;
                cur += col[i][j] != iter;
                col[i][j] = iter;
                if ((i == 0 || i == n - 1) && (j == 0 || j == m - 1)) break;
                if (i == 0 || i == n - 1) di = -di;
                if (j == 0 || j == m - 1) dj = -dj;
            }
            cout << n << ' ' << m << ": " << cur << ' ' << my_solve(n, m) << '\n';
            assert(cur == my_solve(n, m));
        }
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    --n, --m;
    ll cnt = lcm(n, m);
    ll g = gcd(n, m);
    ll g2 = 2 * g;
    ll dos = ((n) / g2) * ((m) / g2);
    ll tres = ((n - g) / g2) * ((m - g) / g2);
    ll distinct = cnt - dos - tres + 1;
    cout << 2 * cnt << ' ' << distinct << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt;
    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
