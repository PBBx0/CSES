#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 2e5;
vector<int> g[N], order;
int val[N], tin[N], tout[N];
void dfs(int v, int par) {
    tin[v] = sz(order);
    order.emplace_back(v);
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
    }
    tout[v] = sz(order);
}

struct FT {
    vector<ll> t;
    FT(int n) : t(n) {}
    ll get(ll p) {
        ll res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }
    void update(ll p, ll add) {
        for (; p < sz(t); p |= p + 1) t[p] += add;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> val[i];
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
    FT ft(n);
    for (int i = 0; i < n; ++i) {
        ft.update(tin[i], val[i]);
        ft.update(tout[i], -val[i]);
    }
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int v, x;
            cin >> v >> x;
            v--;
            int add = x - val[v];
            val[v] += add;
            ft.update(tin[v], add);
            ft.update(tout[v], -add);
        } else if (tp == 2) {
            int v;
            cin >> v;
            v--;
            cout << ft.get(tin[v] + 1) << '\n';
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