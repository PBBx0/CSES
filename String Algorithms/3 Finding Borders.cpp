#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    vector<int> ans, nf(n);
    int l = -1, r = -1;
    for (int i = 1; i < n; ++i) {
        nf[i] = i >= r ? 0 : min(nf[i - l], r - i);
        while (i + nf[i] < n && s[i + nf[i]] == s[nf[i]]) ++nf[i];
        if (i + nf[i] > r) {
            l = i, r = i + nf[i];
        }
        if (i + nf[i] == n) ans.emplace_back(nf[i]);
    }
    reverse(ans.begin(), ans.end());
    for (int el : ans) cout << el << ' ';
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