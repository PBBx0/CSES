#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

void solve() {
    string str;
    cin >> str;
    int n = sz(str);
    vector<pair<char, int>> t(n);
    for (int i = 0; i < n; ++i) t[i] = {str[i], i};
    sort(t.begin(), t.end());
    int p[n];
    for (int i = 0; i < n; ++i) {
        p[t[i].second] = i;
    }
    int x = 0;
    string cur;
    for (int i = 1; i < n; ++i) {
        x = p[x];
        cur += t[x].first;
    }
    reverse(cur.begin(), cur.end());
    cout << cur << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}