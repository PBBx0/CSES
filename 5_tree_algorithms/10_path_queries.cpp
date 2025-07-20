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
vector<int> tin, tout, c;
vector<ll> ans0;
int timer = 0;

void dfs(int v, int par, ll cur_sum) {
    tin[v] = timer++;
    cur_sum += c[v];
    ans0[v] = cur_sum;
    for (int to : g[v]) if (to != par) {
        dfs(to, v, cur_sum);
    }
    tout[v] = timer;
}

struct FT {
    vector<ll> t;

    FT(int n) : t(n) {}

    ll get(int p) {
        ll r = 0;
        for (; p > 0; p &= p - 1) r += t[p - 1];
        return r;
    }

    void upd(int p, int x) {
        for (; p < sz(t); p |= p + 1) t[p] += x;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    c.resize(n);
    for (int& el : c) cin >> el;
    g.resize(n), tin.resize(n), tout.resize(n), ans0.resize(n);

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    dfs(0, 0, 0);

    FT ft(n);

    for (int i = 0; i < q; ++i) {
        int tp, v;
        cin >> tp >> v;
        --v;
        if (tp == 1) {
            int x;
            cin >> x;
            int delta = x - c[v];
            c[v] += delta;
            ft.upd(tin[v], delta);
            ft.upd(tout[v], -delta);
        } else {
            cout << ans0[v] + ft.get(tin[v] + 1) << '\n';
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
