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

const int T = 2e5 + 5;

int mind[T], is_prime[T];
vector<int> primes;

void solve() {
    primes.reserve(T);
    for (int i = 2; i < T; ++i) {
        if (mind[i] == 0) {
            primes.emplace_back(mind[i] = i);
            is_prime[i] = 1;
        }
        for (int j : primes) {
            if (i * j >= T || j > mind[i]) break;
            mind[i * j] = j;
        }
    }
    int n;
    cin >> n;
    int m = n;
    vector<int> ans(n);
    while (m > 0) {
        int j = m;
        for (; j > 0; --j) {
            if (is_prime[m + j]) break;
        }
        if (j == 0) break;
        for (int t = j - 1; t < m; ++t) {
            ans[t] = m - (t - (j - 1));
        }
        m = j - 1;
    }
    for (int x = 1; x <= n; ++x) cout << x << ' ';
    cout << '\n';
    for (int el : ans) cout << el << ' ';
    cout << '\n';
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
