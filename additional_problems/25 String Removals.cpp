#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26;
const ll MOD = 1e9 + 7;
ll cnt = 1, diff[C];
void solve() {
    string s;
    cin >> s;
    for (char c : s) {
        int x = c - 'a';
        ll cur = (cnt - diff[x] + MOD) % MOD;
        cnt = (cnt + cur) % MOD;
        diff[x] = (diff[x] + cur) % MOD;
    }
    cout << (cnt - 1 + MOD) % MOD << '\n';
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