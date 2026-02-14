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

const pair<int, int> moves[] = {
        {-1, 2}, {-1, -2}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {2, 1}, {2, -1}
};


const int T = 50;
const int INF = 1e9;
int dst[T][T];

int get(int x, int y) {
    if (x < T && y < T) {
        return dst[x][y];
    }
    if (x < y) swap(x, y);
    int cnt = max(1, min(x / 2, x - y) - 1);
    x -= 2 * cnt;
    y -= cnt;
    if (y < 0) y = (-y) % 2;
    int ans = cnt;
    cnt = max(0, min(x, y) / 3 - 2);
    ans += 2 * cnt;
    x -= 3 * cnt;
    y -= 3 * cnt;
    return get(x, y) + ans;
}

/*
a + 2b = x + 2m
2a + b = y + 2k

3 (a + b) = x + y
a - b = y - x
*/

void solve() {
    for (int i = 0; i < T; ++i) for (int j = 0; j < T; ++j) {
        dst[i][j] = INF;
    }
    dst[0][0] = 0;
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop_front();
        for (auto [di, dj] : moves) {
            int i1 = i + di, j1 = j + dj;
            if (i1 < 0 || i1 >= T || j1 < 0 || j1 >= T) continue;
            if (dst[i1][j1] == INF) {
                dst[i1][j1] = dst[i][j] + 1;
                q.emplace_back(i1, j1);
            }
        }
    }
    int tt;
    cin >> tt;
    for (int i = 0; i < tt; ++i) {
        int x, y;
        cin >> x >> y;
        cout << get(x - 1, y - 1) << '\n';
    }
//    for (int i = 0; i < T; ++i) {
//        for (int j = 0; j < T; ++j) {
//            int di = abs(i - T / 2);
//            int dj = abs(j - T / 2);
//            cout << get(di, dj) << ' ';
//
//        }
//        cout << '\n';
//    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
