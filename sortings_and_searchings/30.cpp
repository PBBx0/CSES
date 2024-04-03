#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    unordered_map<int, int> cnt;
    ll res = 0;
    int j = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && sum + (cnt[a[j]] == 0) <= k) {
            sum += cnt[a[j]] == 0;
            cnt[a[j]]++;
            j++;
        }
//        cerr << i << ' ' << j << '\n';
        res += (j - i);
        cnt[a[i]]--;
        sum -= cnt[a[i]] == 0;
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}