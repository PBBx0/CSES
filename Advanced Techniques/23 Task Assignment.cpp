#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct edge {
    int from, to, cap, cost, flow = 0;
    edge(int from = 0, int to = 0, int cap = 0, int cost = 0) : \
    from(from), to(to), cap(cap), cost(cost) {}
};
const int N = 403, M = 1e5, INF = 1e9 + 7;
edge E[M];
int d[N], p[N], par[N];
bool used[N];
vector<int> g[N];
void solve() {
    int n;
    cin >> n;
    int top = 0;
    for (int i = 0; i < n; ++i) {
        g[0].emplace_back(top);
        E[top] = {0, i + 1, 1, 0};
        top++;
        g[i + 1].emplace_back(top);
        E[top] = {i + 1, 0, 0, 0};
        top++;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x;
            cin >> x;
            g[i].emplace_back(top);
            E[top] = {i, j + n, 1, x};
            top++;
            g[j + n].emplace_back(top);
            E[top] = {j + n, i, 0, -x};
            top++;
        }
    }
    for (int j = n + 1; j <= n + n; ++j) {
        g[j].emplace_back(top);
        E[top] = {j, n + n + 1, 1, 0};
        top++;
        g[n + n + 1].emplace_back(top);
        E[top] = {n + n + 1, j, 0, 0};
        top++;
    }
    const int n2 = 1 + n + n + 1;
    fill(d, d + N, INF);
    fill(par, par + n2, -1);
    d[0] = 0;
    for (int i = 0; i < n2; ++i) {
        for (int id = 0; id < top; ++id) {
            auto [from, to, cp, cs, fl] = E[id];
            if (cp == fl) continue;
            if (d[to] > d[from] + cs) {
                d[to] = d[from] + cs;
                par[to] = id;
            }
        }
    }
    for (int i = 0; i < n2; ++i) p[i] = d[i];
    ll res = 0;
    for (int _ = 0; _ < n; ++_) {
        assert(d[n2 - 1] != INF);
        for (int v = n2 - 1; par[v] != -1; ) {
            int id = par[v];
            E[id].flow++;
            E[id ^ 1].flow--;
            res += E[id].cost;
            v = E[id].from;
        }
        fill(d, d + n2, INF);
        fill(par, par + n2, -1);
        fill(used, used + n2, false);
        d[0] = 0;
        for (int i = 0; i < n2; ++i) {
            int nv = -1;
            for (int v = 0; v < n2; ++v) if (!used[v]) {
                if (nv == -1 || d[nv] > d[v]) nv = v;
            }
            assert(nv != -1);
            used[nv] = true;
            for (int id : g[nv]) {
                auto [_kek_, to, cp, cs, fl] = E[id];
                if (used[to] || cp == fl) continue;
                if (d[to] > d[nv] + cs + p[nv] - p[to]) {
                    d[to] = d[nv] + cs + p[nv] - p[to];
                    par[to] = id;
                }
            }
        }
        for (int i = 0; i < n2; ++i) p[i] += d[i];
    }
    cout << res << '\n';
    for (int i = 0; i < top; ++i) {
        auto [from, to, cp, cs, fl] = E[i];
        if (from > 0 && from <= n && to > n && to <= n + n && cp == fl) {
            cout << from << ' ' << to - n << '\n';
        }
    }
}

signed main() {
#ifdef LOCAL
    freopen("../test_input.txt", "r", stdin);
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