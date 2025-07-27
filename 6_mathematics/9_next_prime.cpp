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

const int T = 1e6 + 1;
int mind[T];
vector<int> primes;

void solve() {
    primes.reserve(8e4);
    for (int t = 2; t < T; ++t) {
        if (mind[t] == 0) {
            primes.emplace_back(mind[t] = t);
        }
        for (int j : primes) {
            if (t * j >= T || j > mind[t]) break;
            mind[t * j] = j;
        }
    }
    ll n;
    cin >> n;
    for (++n; ; ++n) {
        bool ok = true;
        for (ll t : primes) {
            if (t * t > n) break;
            if (n % t == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << n << '\n';
            return;
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
    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
