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
const int T = 2e5 + 1;
int mind[T];
vector<int> primes;

void solve() {
    primes.reserve(2e4);
    for (int i = 2; i < T; ++i) {
        if (mind[i] == 0) primes.emplace_back(mind[i] = i);
        for (int j : primes) {
            if (i * j >= T || j > mind[i]) break;
            mind[i * j] = j;
        }
    }
    int n;
    cin >> n;
    vector<int> p(n);
    for (int& el : p) {
        cin >> el;
        --el;
    }
    vector<int> used(n);
    map<int, int> deg;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        int t = 0;
        for (int v = i; !used[v]; v = p[v]) {
            used[v] = 1;
            ++t;
        }
        vector<pair<int, int>> factor;
        for (int x = t; x > 1; x /= mind[x]) {
            if (factor.empty() || factor.back().first != mind[x]) factor.emplace_back(mind[x], 1);
            else factor.back().second += 1;
        }
        for (auto [prime, c] : factor) {
            deg[prime] = max(deg[prime], c);
        }
    }
    int ans = 1;
    for (auto [prime, c] : deg) {
        for (int i = 0; i < c; ++i) ans = 1LL * ans * prime % MOD;
    }
    cout << ans << '\n';
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
