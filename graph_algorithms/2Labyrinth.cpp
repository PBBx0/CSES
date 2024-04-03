#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1002, INF = 1e9 + 7;
const vector<pair<int, int>> shift = {
        /* L R D U*/
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}
};
const vector<char> to_char = {
        'U', 'D', 'R', 'L'
};
int dist[N][N], par[N][N];
bool can[N][N];
void solve() {
    for (auto& a : dist)
        for (auto& el : a) el = INF;
    for (auto& a : par)
        for (auto& el : a) el = -1;
    int n, m;
    cin >> n >> m;
    pair<int, int> start, finish;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char tmp;
            cin >> tmp;
            can[i][j] = tmp != '#';
            if (tmp == 'A') {
                start = {i, j};
            }
            if (tmp == 'B') {
                finish = {i, j};
            }
        }
    }
    dist[start.first][start.second] = 0;
    deque<pair<int, int>> dq{start};
    while (!dq.empty()) {
        auto [i, j] = dq.front();
        dq.pop_front();
        for (int k = 0; k < 4; ++k) {
            auto [dx, dy] = shift[k];
            if (!can[i + dx][j + dy]) continue;
            can[i + dx][j + dy] = false;
            dq.emplace_back(i + dx, j + dy);
            dist[i + dx][j + dy] = dist[i][j] + 1;
            par[i + dx][j + dy] = k;
        }
    }
    auto [i1, j1] = finish;
    if (dist[i1][j1] == INF) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n' << dist[i1][j1] << '\n';
    string out;
    int d = dist[i1][j1];
    for (int _ = 0; _ < d; ++_) {
        int k = par[i1][j1];
        out += to_char[k];
        i1 -= shift[k].first;
        j1 -= shift[k].second;
    }
    reverse(out.begin(), out.end());
    cout << out << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}