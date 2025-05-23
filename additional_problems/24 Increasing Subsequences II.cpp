#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll MOD = 1e9 + 7;
struct FT {
    vector<ll> t;
    FT(int n) : t(n) {}
    inline ll get(int p) {
        ll res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res % MOD;
    }
    inline void update(int p, ll x) {
        for (; p < sz(t); p |= p + 1) {
            t[p] = (t[p] + x < MOD ? t[p] + x : t[p] + x - MOD);
        }
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    set<int> s;
    for (int & el : a) {
        cin >> el;
        s.insert(el);
    }
    unordered_map<int, int> mp;
    mp.reserve(sz(s));
    int c = 0;
    for (int el : s) mp[el] = ++c;
    for (int & el : a) el = mp[el];
    FT ft(c + 1);
    ft.update(0, 1);
    for (int x : a) {
        ll cur = ft.get(x);
        ft.update(x, cur);
    }
    cout << (ft.get(c + 1) - 1 + MOD) % MOD << '\n';
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