#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26;
struct node {
    int nx[C], suff = -1;
    node() {
        fill(nx, nx + C, -1);
    }
};
vector<node> t;
const ll MOD = 1e9 + 7;
void solve() {
    int n, m;
    string s;
    cin >> n >> s;
    m = sz(s);
    t.resize(m + 1);
    for (int i = 0; i < m; ++i) {
        t[i].nx[s[i] - 'A'] = i + 1;
    }
    for (int & x : t[0].nx) {
        if (x == -1) x = 0;
    }
    for (int i = 0; i < m; ++i) {
        int x = s[i] - 'A';
        if (t[i].suff == -1) {
            t[i + 1].suff = i;
        } else {
            t[i + 1].suff = t[t[i].suff].nx[x];
        }
        for (int y = 0; y < C; ++y) if (t[i + 1].nx[y] == -1) {
            t[i + 1].nx[y] = t[t[i + 1].suff].nx[y];
        }
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(m));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int v = 0; v < m; ++v) {
            for (int to : t[v].nx) {
                if (to < m) {
                    dp[i + 1][to] += dp[i][v];
                    dp[i + 1][to] %= MOD;
                }
            }
        }
    }
    ll res = 0;
    for (int v = 0; v < m; ++v) {
        res += dp[n][v];
        res %= MOD;
    }
    ll pw = 1;
    for (int i = 0; i < n; ++i) {
        pw = pw * C % MOD;
    }
    cout << (pw - res + MOD) % MOD << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}