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
const int INF = 1e9;

vector<vector<int>> bj, bjmn, g;
vector<int> h;

void dfs(int v, int par) {
    bj[0][v] = par;
    for (int to : g[v]) if (to != par) {
        h[to] = h[v] + 1;
        dfs(to, v);
    }
}

int calc_ans(int a, int b) {
    int ans = h[a] + h[b];
    int mn = INF;
    if (h[a] < h[b]) swap(a, b);
    int k = h[a] - h[b];
    for (int l = 0; l < LOG; ++l) {
        if (k >> l & 1) {
            mn = min(mn, bjmn[l][a]);
            a = bj[l][a];
        }
    }
    if (a == b) return ans - 2 * h[a] + 2 * min(mn, bjmn[0][a]);
    for (int l = LOG - 1; l >= 0; --l) {
        if (bj[l][a] != bj[l][b]) {
            mn = min(mn, bjmn[l][a]);
            mn = min(mn, bjmn[l][b]);
            a = bj[l][a];
            b = bj[l][b];
        }
    }
    mn = min(mn, bjmn[0][a]);
    mn = min(mn, bjmn[0][b]);
    a = bj[0][a];
    return ans - 2 * h[a] + 2 * min(mn, bjmn[0][a]);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n);
    g.resize(n);
    for (int& el : c) cin >> el;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<int> dst(n, -1);
    deque<int> dq;
    for (int i = 0; i < n; ++i) {
        if (c[i]) {
            dst[i] = 0;
            dq.emplace_back(i);
        }
    }
    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();
        for (int to : g[v]) {
            if (dst[to] == -1) {
                dst[to] = dst[v] + 1;
                dq.emplace_back(to);
            }
        }
    }
    bj.resize(LOG, vector<int>(n));
    bjmn.resize(LOG, vector<int>(n));
    h.resize(n);
    dfs(0, 0);
    bjmn[0] = dst;
    for (int l = 1; l < LOG; ++l) {
        for (int v = 0; v < n; ++v) {
            bj[l][v] = bj[l - 1][bj[l - 1][v]];
            bjmn[l][v] = min(bjmn[l - 1][v], bjmn[l - 1][bj[l - 1][v]]);
        }
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << calc_ans(a, b) << '\n';
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
