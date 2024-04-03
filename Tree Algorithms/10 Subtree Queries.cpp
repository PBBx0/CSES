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
    order.emplace_back(val[v]);
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
    }
    tout[v] = sz(order);
}


struct ST {
    int N = 1;
    vector<ll> t;
    ST(vector<int>& a) {
        for (; N < sz(a); N <<= 1);
        t.resize(N << 1);
        for (int i = 0; i < sz(a); ++i) t[i + N] = a[i];
        for (int i = N - 1; i > 0; --i) t[i] = t[i + i] + t[i + i + 1];
    }
    void update(int pos, int x) {
        for (t[pos += N] = x; pos > 1; pos >>= 1)
            t[pos >> 1] = t[pos] + t[pos ^ 1];
    }
    ll get(int l, int r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
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
    ST st(order);
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            st.update(tin[p], x);
        } else if (tp == 2) {
            int p;
            cin >> p;
            p--;
            cout << st.get(tin[p], tout[p]) << '\n';
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
    solve();
    return 0;
}