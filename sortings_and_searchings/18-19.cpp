#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
struct ev {
    int x, val, id;
    ev(int x = 0, int val = 0, int id = -1) : x(x), val(val), id(id) {}
    bool operator< (const ev other) const {
        if (x != other.x)
            return x < other.x;
        return val > other.val;
    }
};
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    void update(int p) {
        for (; p < sz(t); p |= p + 1) {
            t[p]++;
        }
    }
    int gets(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) {
            res += t[p - 1];
        }
        return res;
    }
    int get(int l, int r) {
        return gets(r) - gets(l);
    }
};
void solve() {
    int n;
    cin >> n;
    vector<ev> a;
    set<int> tmp;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        tmp.insert(l);
        tmp.insert(r);
        a.emplace_back(l, r, i);
    }
    unordered_map<int, int> mp;
    int c = 0;
    for (auto el : tmp) {
        if (!mp.contains(el))
            mp[el] = c++;
    }

    for (auto& el : a) {
        el.x = mp[el.x];
        el.val = mp[el.val];
    }
    sort(a.begin(), a.end());
    vector<int> inter(n), outer(n);
    FT ft(c);
                                        vector<int> debug;
    for (auto [l, r, idx] : a) {
        outer[idx] = ft.get(r, c);
        ft.update(r);
                                        debug.emplace_back(r);
    }
    FT ft2(c);
    reverse(a.begin(), a.end());
    for (auto [l, r, idx] : a) {
        inter[idx] = ft2.get(0, r + 1);
        ft2.update(r);
    }
    for (int el : inter) cout << el << ' ';
    cout << '\n';
    for (int el : outer) cout << el << ' ';
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