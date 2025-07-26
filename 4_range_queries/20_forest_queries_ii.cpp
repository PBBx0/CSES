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

struct FT2D {
    vector<vector<int>> t;

    FT2D(int n, int m) {
        t.resize(n, vector<int>(m));
    }

    void update(int x, int y, int delta) {
        for (; x < sz(t); x |= x + 1) {
            for (int y1 = y; y1 < sz(t[0]); y1 |= y1 + 1) {
                t[x][y1] += delta;
            }
        }
    }

    int get(int x, int y) {
        int res = 0;
        for (; x > 0; x &= x - 1) {
            for (int y1 = y; y1 > 0; y1 &= y1 - 1) {
                res += t[x - 1][y1 - 1];
            }
        }
        return res;
    }

    int get(int x1, int y1, int x2, int y2) {
        return get(x2, y2) - get(x1, y2) - get(x2, y1) + get(x1, y1);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<string> f(n);
    for (auto& el : f) cin >> el;
    FT2D ft(n, n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (f[i][j] == '*') ft.update(i, j, 1);
    }
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            if (f[x][y] == '*') {
                f[x][y] = '.';
                ft.update(x, y, -1);
            } else {
                f[x][y] = '*';
                ft.update(x, y, 1);
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            --x1, --y1;
            cout << ft.get(x1, y1, x2, y2) << '\n';
        }
    }
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
