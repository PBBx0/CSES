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

const int M = 3000;

struct edge {
    int from, to, fl, cp;
} E[M];

vector<vector<int>> g;

int edge_count = 0, n;

void add_edge(int from, int to) {
    E[edge_count] = {from, to, 0, 1};
    g[from].emplace_back(edge_count++);
    E[edge_count] = {to, from, 0, 1};
    g[to].emplace_back(edge_count++);
}

vector<int> par;

const int INF = 1e9 + 7;

int bfs(int from, int targ, int cc) {
    fill(all(par), -1);
    par[from] = -2;
    deque<int> q{from};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int id : g[v]) {
            auto [_, to, fl, cp] = E[id];
            if (par[to] == -1 && cp - fl >= cc) {
                par[to] = id;
                q.emplace_back(to);
            }
        }
    }
    if (par[targ] == -1) return 0;
    int mn = INF;
    for (int t = targ; t != from; ) {
        auto [pr, _, fl, cp] = E[par[t]];
        mn = min(mn, cp - fl);
        t = pr;
    }
    for (int t = targ; t != from; ) {
        int id = par[t];
        E[id].fl += mn;
        E[id ^ 1].fl -= mn;
        t = E[id].from;
    }
    return mn;
}

ll maxflow(int from, int targ) {
    ll ans = 0;
    for (int c = INF / 2; c > 0; c /= 2) {
        while (int pushed = bfs(from, targ, c)) {
            ans += pushed;
        }
    }
    return ans;
}


vector<int> restore_cut(int from) {
    fill(all(par), -1);
    par[from] = -2;
    deque<int> q{from};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int id : g[v]) {
            auto [_, to, fl, cp] = E[id];
            if (par[to] == -1 && cp - fl >= 1) {
                par[to] = id;
                q.emplace_back(to);
            }
        }
    }
    vector<int> edges;
    for (int v = 0; v < n; ++v) {
        if (par[v] == -1) continue;
        for (int id : g[v]) {
            if (par[E[id].to] == -1) edges.emplace_back(id);
        }
    }
    return edges;
}

void solve() {
    int m;
    cin >> n >> m;
    g.resize(n), par.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        add_edge(a, b);
    }
    maxflow(0, n - 1);
    auto cut_edges = restore_cut(0);
    cout << sz(cut_edges) << '\n';
    for (int i : cut_edges) {
        cout << E[i].from + 1 << ' ' << E[i].to + 1 << '\n';
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
