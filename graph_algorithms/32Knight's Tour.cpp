#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
constexpr int T = 8, di[]{1, 2, 2, 1, -1, -2, -2, -1}, dj[]{2, 1, -1, -2, -2, -1, 1, 2};
constexpr bool inside(int x, int y) {
    return x >= 0 && x < T && y >= 0 && y < T;
}
int a[T][T];
int cnt[T][T];
void process(int x, int y, int i) {
    for (int k = 0; k < T; ++k) {
        int i1 = x + di[k], j1 = y + dj[k];
        if (inside(i1, j1)) cnt[i1][j1]--;
    }
    a[x][y] = i;
    if (i == 64) {
        for (auto& ar : a) {
            for (auto el : ar) cout << el << ' ';
            cout << '\n';
        }
        exit(0);
    }
    int x1 = -1, y1 = -1;
    for (int k = 0; k < T; ++k) {
        int i1 = x + di[k], j1 = y + dj[k];
        if (!inside(i1, j1) || a[i1][j1] != 0) continue;
        if (x1 == -1 || cnt[i1][j1] < cnt[x1][y1]) {
            x1 = i1, y1 = j1;
        }
    }
    process(x1, y1, i + 1);
}
void solve() {
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j){
            for (int k = 0; k < T; ++k) {
                int i1 = i + di[k], j1 = j + dj[k];
                cnt[i][j] += inside(i1, j1);
            }
        }
    }
    int x, y;
    cin >> y >> x;
    process(--x, --y, 1);
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
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