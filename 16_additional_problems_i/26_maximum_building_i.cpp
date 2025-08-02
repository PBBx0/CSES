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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> f(n);
    for (auto& el : f) cin >> el;
    vector<int> dp(m), lb(m), rb(m), s;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == '*') dp[j] = 0;
            else ++dp[j];
        }
        fill(all(lb), -1);
        fill(all(rb), m);
        s.clear();
        for (int j = 0; j < m; ++j) {
            while (!s.empty() && dp[s.back()] > dp[j]) {
                rb[s.back()] = j;
                s.pop_back();
            }
            lb[j] = s.empty() ? -1
                    : dp[s.back()] == dp[j] ? lb[s.back()]
                    : s.back();
            s.emplace_back(j);
        }
        for (int j = 0; j < m; ++j) {
            ans = max(ans, dp[j] * (rb[j] - lb[j] - 1));
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
