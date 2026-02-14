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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> anime(n);
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        --x;
        anime[x] = true;
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }

    vector<array<int, 2>> nearest(n);
    vector<array<int, 2>> dst(n, {-1, -1});
    vector<int> cnt(n);
    deque<pair<int, int>> dq;
    for (int i = 0; i < n; ++i) {
        if (!anime[i]) continue;
        ++cnt[i];
        nearest[i][0] = i;
        dst[i][0] = 0;
        dq.emplace_back(i, 0);
    }
    while (!dq.empty()) {
        auto [v, id] = dq.front();
        dq.pop_front();
        for (int to : g[v]) {
            if (dst[to][0] == -1) {
                dst[to][0] = dst[v][id] + 1;
                nearest[to][0] = nearest[v][id];
                dq.emplace_back(to, 0);
            } else if (nearest[to][0] != nearest[v][id] && dst[to][1] == -1) {
                dst[to][1] = dst[v][id] + 1;
                nearest[to][1] = nearest[v][id];
                dq.emplace_back(to, 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << dst[i][anime[i]] << ' ';
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
