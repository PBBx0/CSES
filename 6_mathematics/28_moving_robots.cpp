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
using ld = long double;

const int T = 8;

ld prob_empty[T][T];
ld dp[T][T];
ld dp2[T][T];

void solve() {
    int k;
    cin >> k;
    for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
        prob_empty[i][j] = 1;
    }
    for (int i0 = 0; i0 < T; ++i0) for (int j0 = 0; j0 < T; ++j0) {
        for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
            dp[i][j] = 0;
        }
        dp[i0][j0] = 1;
        for (int it = 0; it < k; ++it) {
            for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
                dp2[i][j] = 0;
            }
            for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
                vector<pair<int, int>> moves;
                for (auto [x, y]: initializer_list<pair<int, int>>{{i + 1, j},
                                                                           {i - 1, j},
                                                                           {i,     j + 1},
                                                                           {i,     j - 1}}) {
                    if (x >= 0 && x < T && y >= 0 && y < T) moves.emplace_back(x, y);
                }
                ld prob = 1. / sz(moves);
                for (auto [x, y]: moves) dp2[x][y] += prob * dp[i][j];
            }
            swap(dp, dp2);
        }
        for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
            prob_empty[i][j] *= 1 - dp[i][j];
        }
    }
    ld ans = 0;
    for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
        ans += prob_empty[i][j];
    }
    printf("%.6Lf", ans);
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
