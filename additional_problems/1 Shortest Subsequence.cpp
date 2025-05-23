#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
int to_int(char x) {
    if (x == 'A') return 0;
    if (x == 'C') return 1;
    if (x == 'G') return 2;
    return 3;
}
char to_char(int x) {
    if (x == 0) return 'A';
    if (x == 1) return 'C';
    if (x == 2) return 'G';
    return 'T';
}
void solve() {
    string str;
    cin >> str;
    int n = sz(str);
    vector<int> dp(n + 2, n + 1), nxt(n + 1, n + 1), pass(n + 2);
    dp[n + 1] = 0;
    dp[n] = 1;
    int pos[]{n + 1, n + 1, n + 1, n + 1};
    for (int i = n - 1; i >= 0; --i) {
        int x = to_int(str[i]);
        pos[x] = i + 1;
        for (int d = 0; d < 4; ++d) {
            if (dp[i] > dp[pos[d]] + 1) {
                dp[i] = dp[pos[d]] + 1;
                nxt[i] = pos[d];
                pass[i] = d;
            }
        }
    }
    for (int v = 0; v <= n; v = nxt[v]) {
        cout << to_char(pass[v]);
    }
    cout << '\n';
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