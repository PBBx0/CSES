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
    string s;
    cin >> s;
    vector<int> id(26, -1);
    int c = 0;
    for (char el : s) {
        if (id[el - 'a'] == -1) id[el - 'a'] = c++;
    }
    map<vector<int>, int> pref_cnt;
    vector<int> cur_cnt(c, 0);
    pref_cnt[cur_cnt] += 1;
    ll ans = 0;
    for (int i = 0; i < sz(s); ++i) {
        cur_cnt[id[s[i] - 'a']] += 1;
        vector<int> cur2 = cur_cnt;
        int mn = *min_element(all(cur2));
        for (int& el : cur2) el -= mn;
        ans += pref_cnt[cur2];
        ++pref_cnt[cur2];
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
