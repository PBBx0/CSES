#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
constexpr pair<int, int> shift[4] {
        /* U D R L */
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}
};
constexpr char to_char[]{'U', 'D', 'R', 'L'};
constexpr int N = 1002, INF = 1e9 + 7;
int tp[N][N], distm[N][N], dist[N][N], par[N][N];
void solve() {
    for (auto& a : distm) for (auto& el : a) el = INF;
    for (auto& a : dist) for (auto& el : a) el = INF;
    for (auto& a : par) for (auto& el : a) el = -1;
    int n, m;
    cin >> n >> m;
    int ih, jh;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char t;
            cin >> t;
            switch (t) {
                case '.':
                    tp[i][j] = 1;
                    break;
                case 'M':
                    tp[i][j] = 2;
                    break;
                case 'A':
                    ih = i, jh = j;
                    tp[i][j] = 3;
                    break;
            }
        }
    }
    vector<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) if (tp[i][j] == 2) {
            q.emplace_back(i, j);
            distm[i][j] = 0;
        }
    }
    for (int st = 0; st < sz(q); ++st) {
        auto [i, j] = q[st];
        for (auto [di, dj] : shift) {
            int i1 = i + di, j1 = j + dj;
            if (distm[i1][j1] == INF && tp[i1][j1] != 0) {
                distm[i1][j1] = distm[i][j] + 1;
                q.emplace_back(i1, j1);
            }
        }
    }
    q.clear();
    q.emplace_back(ih, jh);
    dist[ih][jh] = 0;
    for (int st = 0; st < sz(q); ++st) {
        auto [i, j] = q[st];
        for (int k = 0; k < 4; ++k) {
            int i1 = i + shift[k].first, j1 = j + shift[k].second;
            if (tp[i1][j1] != 0 && dist[i1][j1] == INF && distm[i1][j1] > dist[i][j] + 1) {
                dist[i1][j1] = dist[i][j] + 1;
                par[i1][j1] = k;
                q.emplace_back(i1, j1);
            }
        }
    }
    int ir = -1, jr = -1;
    for (int i = 1; i <= n; ++i) {
        if (dist[i][1] != INF) {
            ir = i, jr = 1;
        }
        if (dist[i][m] != INF) {
            ir = i, jr = m;
        }
    }
    for (int j = 1; j <= m; ++j) {
        if (dist[1][j] != INF) {
            ir = 1, jr = j;
        }
        if (dist[n][j] != INF) {
            ir = n, jr = j;
        }
    }
    if (ir == -1) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n' << dist[ir][jr] << '\n';
    string out;
    while (par[ir][jr] != -1) {
        int k = par[ir][jr];
        out += to_char[k];
        ir -= shift[k].first;
        jr -= shift[k].second;
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