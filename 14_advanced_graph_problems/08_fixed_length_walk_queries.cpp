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

const int INF = 1e9;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n * 2);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a << 1 | 0].emplace_back(b << 1 | 1);
        g[b << 1 | 0].emplace_back(a << 1 | 1);
        g[a << 1 | 1].emplace_back(b << 1 | 0);
        g[b << 1 | 1].emplace_back(a << 1 | 0);
    }
    vector<array<int, 4>> queries(q);
    int iter = 0;
    for (auto& [a, b, c, i] : queries) {
        cin >> a >> b >> c;
        --a, --b;
        i = iter++;
    }

    vector<int> dst(2 * n);
    deque<int> dq;
    auto bfs = [&](int from) {
        from <<= 1;
        fill(all(dst), -1);
        dst[from] = 0;
        dq.emplace_back(from);
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
    };


    sort(all(queries));
    vector<bool> ans(q);
    int last = -1;
    for (auto [f, t, c, i] : queries) {
        if (f != last) {
            bfs(last = f);
        }
        f <<= 1;
        (t <<= 1) |= (c & 1);
        ans[i] = dst[t] != -1 && dst[t] <= c;
    }
    for (bool el : ans) {
        cout << (el ? "YES" : "NO") << '\n';
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
