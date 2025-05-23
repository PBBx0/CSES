#include <bits/stdc++.h>
#define sz(n) (int)(n).size()

using namespace std;
using ll = int64_t;
const int a[9][5] = {
        {4, 4, 5, 5, 4},
        {4, 6, 5, 4, 4},
        {5, 6, 6, 5, 5},
        {5, 5, 4, 4, 5},
        {6, 6, 4, 6, 6},
        {4, 6, 5, 5, 6},
        {4, 4, 5, 4, 4},
        {5, 6, 6, 4, 5},
        {5, 5, 6, 5, 5}
};
void solve() {
    int n, m;
    cin >> n >> m;
    if (n * m % 3 != 0 || (n == 3 && m % 2 == 1) || (m == 3 && n % 2 == 1) || m == 1 || n == 1) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    bool was_swap = m % 3 == 0;
    if (was_swap) swap(n, m);
    int ans[n][m];
    int j = 0;
    bool flag = true;
    while (j + 3 < m || m - j == 4 || m - j == 2) {
        for (int i = 0; i < n; ++i) {
            if (flag) {
                ans[i][j] = i % 3 == 0 ? 0 : 1;
                ans[i][j + 1] = i % 3 == 2 ? 1 : 0;
            } else {
                ans[i][j + 1] = i % 3 == 0 ? 1 : 0;
                ans[i][j] = i % 3 == 2 ? 0 : 1;
            }
        }
        flag = !flag;
        j += 2;
    }
    if (j != m) {
        assert(m - j == 3);
        int i = 0;
        flag = true;
        while (n - i != 0 && n - i != 9) {
            if (flag) {
                ans[i][j] = ans[i + 1][j] = ans[i + 1][j + 1] = 2;
                ans[i][j + 1] = ans[i][j + 2] = ans[i + 1][j + 2] = 3;
            } else {
                ans[i][j] = ans[i + 1][j] = ans[i][j + 1] = 3;
                ans[i + 1][j + 1] = ans[i][j + 2] = ans[i + 1][j + 2] = 2;
            }
            flag = !flag;
            i += 2;
        }
        j -= 2;
        if (i != n) {
            assert(n - i == 9 && m - j == 5);
            for (int i1 = 0; i1 < 9; ++i1) {
                for (int j1 = 0; j1 < 5; ++j1) {
                    ans[i + i1][j + j1] = a[i1][j1];
                }
            }
        }
    }
    if (was_swap) {
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i)
                cout << char('A' + ans[i][j]);
            cout << '\n';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << char('A' + ans[i][j]);
            cout << '\n';
        }
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
    int tt;
    cin >> tt;
    while (tt--)
        solve();
    return 0;
}
