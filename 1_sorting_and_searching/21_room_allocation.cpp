#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> seg(n);
    int j = 0;
    vector<int> xx;
    for (auto &[l, r, i]: seg) {
        cin >> l >> r;
        i = j++;
    }
    sort(all(seg));
    set<pair<int, int>> rooms;
    vector<int> ans(n);
    for (auto [l, r, id] : seg) {
        auto iter = rooms.lower_bound({l, -1});
        int k = sz(rooms);
        if (iter != rooms.begin()) {
            --iter;
            k = iter->second;
            rooms.erase(iter);
        }
        ans[id] = k;
        rooms.emplace(r, k);
    }
    cout << sz(rooms) << '\n';
    for (int el : ans) cout << el + 1 << ' ';
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
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}