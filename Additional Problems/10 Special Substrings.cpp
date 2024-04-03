#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int C = 26;
void solve() {
    string s;
    cin >> s;
    bool used1[C], used2[C];
    fill(used1, used1 + C, false);
    for (char ch : s) used1[ch - 'a'] = true;
    int all_cnt = 0;
    for (int i = 0; i < C; ++i) all_cnt += used1[i];
    map<array<int, C>, int> cnt;
    array<int, C> cur{};
    cnt[cur] = 1;
    fill(used2, used2 + C, false);
    int n = sz(s);
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        int x = s[i] - 'a';
        cur[x]++;
        if (!used2[x]) {
            all_cnt--;
            used2[x] = true;
        }
        if (!all_cnt) {
            int mi = n;
            for (int j = 0; j < C; ++j) if (used1[j]) {
                mi = min(mi, cur[j]);
            }
            for (int j = 0; j < C; ++j) if (used1[j]) {
                cur[j] -= mi;
            }
        }
        res += cnt[cur]++;
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