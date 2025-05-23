#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    void upd(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] += x;
    }
    void update(int l, int r, int x) {
        upd(l, x), upd(r, -x);
    }
    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
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
    mp.reserve(n);
    int c = 0;
    for (int el : s) mp[el] = c++;
    for (int & el : a) el = mp[el];
    int pos[n];
    for (int i = 0; i < n; ++i) pos[a[i]] = i;
    FT f1(n + 1), f2(n + 1);
    ll ans = 0;
    for (int x = 0; x < n; ++x) {
        int left = pos[x] + f1.get(pos[x] + 1);
        int right = n - 1 - pos[x] + f2.get(pos[x] + 1);
        if (left <= right) {
            ans += left;
        } else {
            ans += right;
        }
        f1.update(pos[x], n + 1, -1);
        f2.update(0, pos[x] + 1, -1);
    }
    cout << ans << '\n';
}

signed main() {
    int tt = 1;
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    cin >> tt;
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    while (tt--) solve();
    return 0;
}