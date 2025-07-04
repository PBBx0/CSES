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

mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

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
    vector<pair<int, int>> good;
    int lowest = 9;
    for (int k = 0; k < T; ++k) {
        int i1 = x + di[k], j1 = y + dj[k];
        if (!inside(i1, j1) || a[i1][j1] != 0) continue;
        if (cnt[i1][j1] < lowest) {
            good.clear();
            lowest = cnt[i1][j1];
        }
        if (cnt[i1][j1] == lowest) {
            good.emplace_back(i1, j1);
        }
    }
    for (auto [x1, y1] : good) {
        process(x1, y1, i + 1);
    }
    a[x][y] = 0;
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
