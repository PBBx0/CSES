#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26;
struct node {
    bool term = false;
    int nx[C];
    node() {
        fill(nx, nx + C, -1);
    }
};
vector<node> t(1);
void add_word(string & str) {
    int v = 0;
    for (char ch : str) {
        int x = ch - 'a';
        if (t[v].nx[x] == -1) {
            t[v].nx[x] = sz(t);
            t.emplace_back();
        }
        v = t[v].nx[x];
    }
    t[v].term = true;
}
const ll MOD = 1e9 + 7;
void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string cur;
        cin >> cur;
        add_word(cur);
    }
    vector<ll> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        int v = 0;
        for (int j = i; j < n; ++j) {
            int x = s[j] - 'a';
            if (t[v].nx[x] == -1) {
                break;
            }
            v = t[v].nx[x];
            if (t[v].term) {
                dp[j + 1] = (dp[i] + dp[j + 1]) % MOD;
            }
        }
    }
    cout << dp[n] << '\n';
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