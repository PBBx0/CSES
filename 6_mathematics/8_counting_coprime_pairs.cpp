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
vector<int> primes;
int mind[T];

void solve() {
    primes.reserve(8e4);
    for (int i = 2; i < T; ++i) {
        if (mind[i] == 0) {
            primes.emplace_back(mind[i] = i);
        }
        for (int j : primes) {
            if (i * j >= T || j > mind[i]) break;
            mind[i * j] = j;
        }
    }

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ll ans = 0;
    vector<int> cnt(T);
    for (int x : a) {
        vector<int> p;
        for (int t = x; t > 1; t /= mind[t]) {
            if (p.empty() || p.back() != mind[t]) p.emplace_back(mind[t]);
        }
        int k = sz(p);
        int cur_ans = 0;
        for (int mask = 0; mask < (1 << k); ++mask) {
            int cur = 1;
            int sgn = 1;
            for (int j = 0; j < k; ++j) {
                if (mask >> j & 1) {
                    cur *= p[j];
                    sgn *= -1;
                }
            }
            cur_ans += sgn * cnt[cur];
        }
        ans += cur_ans;
        for (int mask = 0; mask < (1 << k); ++mask) {
            int cur = 1;
            for (int j = 0; j < k; ++j) {
                if (mask >> j & 1) {
                    cur *= p[j];
                }
            }
            ++cnt[cur];
        }
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
