#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    int n;
    cin >> n;
    vector dst(n, vector<int>(n, -1));
    dst[0][0] = 0;
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        for (auto [dx, dy] : vector<pair<int, int>>{{1, 2}, {2, 1}}) {
            for (auto px : {-1, 1}) for (auto py : {-1, 1}) {
                int x1 = x + dx * px, y1 = y + dy * py;
                if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) continue;
                int& d = dst[x1][y1];
                if (d == -1) {
                    d = dst[x][y] + 1;
                    q.emplace_back(x1, y1);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dst[i][j] << ' ';
        }
        cout << '\n';
    }
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