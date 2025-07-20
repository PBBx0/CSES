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

struct ST {
    int N = 1;
    vector<ll> t;

    ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) {
            t[i] = t[i << 1 | 0] + t[i << 1 | 1];
        }
    }

    ll get(int l, int r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }

    void update(int pos, ll x) {
        t[pos += N] = x;
        for (pos >>= 1; pos > 0; pos >>= 1) t[pos] = t[pos << 1 | 0] + t[pos << 1 | 1];
    }
};

vector<vector<int>> g;
vector<int> tin, tout;
int timer = 0;

void dfs(int v, int par) {
    tin[v] = timer++;
    for (int to : g[v]) if (to != par) {
        dfs(to, v);
    }
    tout[v] = timer;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n);
    for (int& el : c) cin >> el;
    g.resize(n), tin.resize(n), tout.resize(n);

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    dfs(0, 0);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[tin[i]] = c[i];
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int tp, v;
        cin >> tp >> v;
        --v;
        if (tp == 1) {
            int x;
            cin >> x;
            a[tin[v]] = c[v] = x;
            st.update(tin[v], x);
        } else {
            cout << st.get(tin[v], tout[v]) << '\n';
        }
    }
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
