#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;

void solve() {
    string s;
    cin >> s;
    string str = "#";
    for (char x : s) str += x, str += "#";
    int n = sz(str);
    vector<int> p(n);
    int l = -1, r = -1;
    int len = 0, pos = 0;
    for (int i = 0; i < n; ++i) {
        p[i] = i >= r ? 1 : min(r - i, p[r + l - i]);
        while (i - p[i] >= 0 && i + p[i] < n && str[i - p[i]] == str[i + p[i]]) p[i]++;
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
        if (p[i] - 1 > len) {
            len = p[i] - 1;
            pos = i;
        }
    }
//    cerr << str << '\n';
//    for (int el : p) cerr << el << ' ';
//    cerr << len << '\n';
    string res;
    for (int j = pos - len; j <= pos + len; ++j) {
        if (str[j] != '#') res += str[j];
    }
    cout << res << '\n';
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