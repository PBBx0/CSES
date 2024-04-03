#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
const int T = 8;
bool block[T][T], used_ver[T], used_diag1[T + T], used_diag2[T + T];
int res = 0;
int get_diag1(int row, int col) {
    return T + row - col;
}
int get_diag2(int row, int col) {
    return row + col;
}
void gen(int i) {
    if (i == T) {
        ++res;
        return;
    }
    for (int j = 0; j < T; ++j) {
        if (block[i][j]) continue;
        if (used_ver[j]) continue;
        if (used_diag1[get_diag1(i, j)]) continue;
        if (used_diag2[get_diag2(i, j)]) continue;
        used_ver[j] = true;
        used_diag1[get_diag1(i, j)] = true;
        used_diag2[get_diag2(i, j)] = true;
        gen(i + 1);
        used_ver[j] = false;
        used_diag1[get_diag1(i, j)] = false;
        used_diag2[get_diag2(i, j)] = false;
    }
}
void solve() {
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < T; ++j) {
            char x;
            cin >> x;
            block[i][j] = x == '*';
        }
    }
    gen(0);
    cout << res << '\n';
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