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

int get_int(char x) {
    return x == 'A' ? 0
            : x == 'C' ? 1
            : x == 'G' ? 2
            : 3;
}

const string to_char = "ACGT";

void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    vector<int> dp(n + 2);
    dp[n] = 1;
    vector<array<int, 4>> nxt(n + 1);
    nxt[n] = {n, n, n, n};
    for (int i = n - 1; i >= 0; --i) {
        nxt[i] = nxt[i + 1];
        nxt[i][get_int(s[i])] = i;
        dp[i] = n;
        for (int j = 0; j < 4; ++j) {
            dp[i] = min(dp[i], 1 + dp[nxt[i][j] + 1]);
        }
    }
    string ans;
    for (int i = 0; i <= n;) {
        for (int j = 0; j < 4; ++j) {
            if (dp[i] == 1 + dp[nxt[i][j] + 1]) {
                ans += to_char[j];
                i = nxt[i][j] + 1;
                break;
            }
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
