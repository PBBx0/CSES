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

const int M = 4000, INF = 1e9 + 7;

struct edge {
    int from, to, fl, cp;
} E[M];

int edge_count = 0;
vector<vector<int>> g;
vector<int> par;

void add_edge(int from, int to) {
    E[edge_count] = {from, to, 0, 1};
    g[from].emplace_back(edge_count++);
    E[edge_count] = {to, from, 0, 0};
    g[to].emplace_back(edge_count++);
}

int bfs(int from, int targ, int c) {
    fill(all(par), -1);
    par[from] = -2;
    deque<int> q{from};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int id : g[v]) {
            auto [_, to, fl, cp] = E[id];
            if (par[to] == -1 && cp - fl >= c) {
                par[to] = id;
                q.emplace_back(to);
            }
        }
    }
    if (par[targ] == -1) return 0;
    int pushed = INF;
    for (int t = targ; t != from; ) {
        auto [pr, _, fl, cp] = E[par[t]];
        pushed = min(pushed, cp - fl);
        t = pr;
    }
    for (int t = targ; t != from; ) {
        int id = par[t];
        E[id].fl += pushed;
        E[id ^ 1].fl -= pushed;
        t = E[id].from;
    }
    return pushed;
}

ll maxflow(int from, int targ) {
    ll ans = 0;
    for (int c = INF / 2; c > 0; c /= 2) {
        while (int pushed = bfs(from, targ, c)) ans += pushed;
    }
    return ans;
}

vector<vector<int>> decompose(int from, int targ, int cnt) {
    vector<vector<int>> res(cnt);
    for (int i = 0; i < cnt; ++i) {
        fill(all(par), -1);
        par[from] = -2;
        deque<int> q{from};
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int id : g[v]) {
                auto [_, to, fl, cp] = E[id];
                if (par[to] == -1 && fl > 0) {
                    par[to] = id;
                    q.emplace_back(to);
                }
            }
        }
        assert(par[targ] != -1);
        res[i].emplace_back(targ);
        for (int t = targ; t != from; ) {
            int id = par[t];
            E[id].fl -= 1;
            E[id ^ 1].fl += 1;
            t = E[id].from;
            res[i].emplace_back(t);
        }
        reverse(all(res[i]));
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n), par.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        add_edge(a, b);
    }
    int cnt = maxflow(0, n - 1);
    auto routes = decompose(0, n - 1, cnt);
    cout << cnt << '\n';
    for (const auto& r : routes) {
        cout << sz(r) << '\n';
        for (int el : r) cout << el + 1 << ' ';
        cout << '\n';
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
