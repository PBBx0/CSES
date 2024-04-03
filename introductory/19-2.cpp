#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

string s;
constexpr int N = 48, T = 7;
const vector<pair<int, int>> shift = {
        {1, 0}, {-1, 0}, {0, -1}, {0, 1}// R L U D
};
bool used[T + 2][T + 2];
int ans = 0;
void gen(int i, int x, int y, int from = -1) {
    if (x == 1 && y == 7) {
        ans += i == N;
        return;
    }
    if (i == N) {
        return;
    }
    bool can[4];
    int cnt_can = 0;
    for (int t = 0; t < 4; ++t) {
        auto [dx, dy] = shift[t];
        can[t] = !used[x + dx][y + dy];
        cnt_can += can[t];
    }
    if (from != -1 && !can[from] && cnt_can != 1) return;
    used[x][y] = true;
    switch (s[i]) {
        case 'R':
            if (can[0]) gen(i + 1, x + 1, y, 0);
            break;
        case 'L':
            if (can[1]) gen(i + 1, x - 1, y, 1);
            break;
        case 'U':
            if (can[2]) gen(i + 1, x, y - 1, 2);
            break;
        case 'D':
            if (can[3]) gen(i + 1, x, y + 1, 3);
            break;
        default:
            for (int k = 0; k < 4; ++k) if (can[k]) {
                    auto [dx, dy] = shift[k];
                    gen(i + 1, x + dx, y + dy, k);
                }
    }
    used[x][y] = false;
}
void solve() {
    cin >> s;
    for (int i = 0; i < T + 2; ++i) {
        used[0][i] = used[T + 1][i] = used[i][0] = used[i][T + 1] = true;
    }
    gen(0, 1, 1);
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    auto start = clock();
    solve();
    cerr << (clock() - start) * 1000 / CLOCKS_PER_SEC << '\n';
    return 0;
}