#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

vector<vector<int>> g;
vector<int> up, tin, s, h, par;

int calc_size(int v, int p) {
    for (int& to : g[v]) if (to != p) {
        h[to] = h[v] + 1;
        par[to] = v;
        s[v] += calc_size(to, v);
        if (s[to] > s[g[v][0]]) swap(g[v][0], to);
    }
    return ++s[v];
}

void dfs(int v, int& timer) {
    tin[v] = timer++;
    for (int to : g[v]) if (to != par[v]) {
        up[to] = to == g[v][0] ? up[v] : to;
        dfs(to, timer);
    }
}

struct ST {
    int N = 1;
    vector<int> t;

    void build(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) {
            t[i] = max(t[i << 1 | 0], t[i << 1 | 1]);
        }
    }

    int get(int l, int r) {
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }

    void update(int pos, ll x) {
        t[pos += N] = x;
        for (pos >>= 1; pos > 0; pos >>= 1) t[pos] = max(t[pos << 1 | 0], t[pos << 1 | 1]);
    }
};

ST sgt;

int hld_query(int a, int b) {
    int res = 0;
    while (up[a] != up[b]) {
        if (h[up[a]] < h[up[b]]) swap(a, b);
        res = max(res, sgt.get(tin[up[a]], tin[a] + 1));
        a = par[up[a]];
    }
    if (h[a] < h[b]) swap(a, b);
    res = max(res, sgt.get(tin[b], tin[a] + 1));
    return res;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    g.resize(n);
    up.resize(n);
    tin.resize(n);
    s.resize(n);
    h.resize(n);
    par.resize(n);

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    calc_size(0, 0);
    int timer = 0;
    dfs(0, timer);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[tin[i]] = a[i];
    sgt.build(c);

    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            sgt.update(tin[p], x);
        } else {
            int u, v;
            cin >> u >> v;
            --u, --v;
            cout << hld_query(u, v) << ' ';
        }
    }
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
