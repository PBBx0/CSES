#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int T = 9;
const pair<int, int> swaps[12] {
        {0, 1}, {1, 2},
        {3, 4}, {4, 5},
        {6, 7}, {7, 8},
        {0, 3}, {1, 4}, {2, 5},
        {3, 6}, {4, 7}, {5, 8},
};
ll mask(array<int, T> & a) {
    ll res = 0, d = 0;
    for (ll x : a) {
        res |= (x << d);
        d += 4;
    }
    return res;
}
array<int, T> decode(ll m) {
    array<int, T> res{};
    for (int i = 0; i < T; ++i) {
        res[i] = m % (1LL << 4);
        m >>= 4;
    }
    return res;
}
void solve() {
    array<int, T> good{};
    for (int i = 0; i < T; ++i) good[i] = i + 1;
    ll good_mask = mask(good);
    array<int, T> a{};
    for (int & el : a) cin >> el;
    ll m1 = mask(a);
    if (good_mask == m1) {
        cout << 0 << '\n';
        return;
    }
    unordered_map<ll, int> d;
    d[m1] = 0;
    vector<pair<ll, int>> q;
    q.emplace_back(m1, 0);
    for (int st = 0; st < sz(q); ++st) {
        auto [m, ans] = q[st];
        auto b = decode(m);
        for (auto [i, j] : swaps) {
            swap(b[i], b[j]);
            ll m2 = mask(b);
            if (!d.contains(m2)) {
                if (m2 == good_mask) {
                    cout << ans + 1 << '\n';
                    return;
                }
                d[m2] = ans + 1;
                q.emplace_back(m2, ans + 1);
            }
            swap(b[i], b[j]);
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