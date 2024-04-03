#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 1e6 + 1;
int cnt[T];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    for (int el : a) {
        cnt[el]++;
    }
    for (int res = T - 1; ; res--) {
        int cur_cnt = 0;
        for (int x = 0; x < T; x += res) cur_cnt += cnt[x];
        if (cur_cnt >= 2) {
            cout << res << '\n';
            return;
        }
    }
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