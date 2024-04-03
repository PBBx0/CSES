#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }
    void update(int p) {
        for (; p < sz(t); p |= p + 1) t[p]++;
    }
};
struct FT2 {
    vector<int> t;
    FT2(int n) : t(n) {}
    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res = max(res, t[p - 1]);
        return res;
    }
    void update(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] = max(t[p], x);
    }
};
void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int & el : a) {
        cin >> el;
        el--;
    }
    FT ft(n);
    ll invs = 0;
    for (int el : a) {
        invs += ft.get(n) - ft.get(el);
        ft.update(el);
    }
    cout << invs << ' ';
    int col[n];
    fill(col, col + n, 0);
    int c = 0;
    for (int v : a) if (col[v] == 0) {
        c++;
        for (int u = v; col[u] == 0; u = a[u]) col[u] = 1;
    }
    cout << n - c << ' ';
    FT2 dp(n);
    for (int el : a) {
        dp.update(el, dp.get(el) + 1);
    }
    cout << n - dp.get(n) << ' ';
    int pos[n];
    for (int i = 0; i < n; ++i) pos[a[i]] = i;
    int pr = n, cnt = n;
    for (int x = n - 1; x >= 0; --x) {
        if (pos[x] < pr) {
            pr = pos[x];
            cnt--;
        } else {
            break;
        }
    }
    cout << cnt << '\n';
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