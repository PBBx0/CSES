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

const int LOG = 19;
vector<int> h, sm, c;
vector<vector<int>> g, bj;
int k = 0;


void dfs_sum(int v, int par) {
    bj[0][v] = par;
    sm[v] += c[v];
    for (int to: g[v]) if (to != par) {
        h[to] = h[v] + 1;
        dfs_sum(to, v);
        sm[v] += sm[to];
    }
}

int put_up(int v) {
    if (sm[v] != 0) return v;
    for (int l = LOG - 1; l >= 0; --l) {
        if (sm[bj[l][v]] == 0) v = bj[l][v];
    }
    return bj[0][v];
}

int get_ans(int a, int b) {
    int ans = h[a] + h[b];
    a = put_up(a);
    b = put_up(b);
    ans -= h[a];
    ans -= h[b];
    int ans2 = h[a] + h[b];
    if (h[a] < h[b]) swap(a, b);
    int len = h[a] - h[b];
    for (int l = 0; l < LOG; ++l) {
        if (len >> l & 1) {
            a = bj[l][a];
        }
    }
    if (a != b) {
        for (int l = LOG - 1; l >= 0; --l) {
            if (bj[l][a] != bj[l][b]) {
                a = bj[l][a], b = bj[l][b];
            }
        }
        a = bj[0][a];
    }
    ans2 -= 2 * h[a];
    return ans + 2 * (k - 1) - ans2;
}

void solve() {
    int n, q;
    cin >> n >> q;
    h.resize(n), sm.resize(n), c.resize(n), g.resize(n);
    bj.resize(LOG, vector<int>(n));
    for (int& el : c) cin >> el;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    int root = 0;
    while (c[root] == 0) ++root;
    dfs_sum(root, root);
    for (int l = 1; l < LOG; ++l) {
        for (int i = 0; i < n; ++i) {
            bj[l][i] = bj[l - 1][bj[l - 1][i]];
        }
    }
    for (int i = 0; i < n; ++i) k += sm[i] > 0;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << get_ans(a, b) << '\n';
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
