#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
constexpr int N = 1 << 10;
struct ST {
    int t[N + N];
    void update(int p, int x) {
        for (p += N; p > 0; p >>= 1)
            t[p] += x;
    }
    int get(int l, int r) {
        int res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
ST t[N + N];
void update(int p1, int p2, int x) {
    for (p1 += N; p1 > 0; p1 >>= 1) {
        t[p1].update(p2, x);
    }
}
int get(int u, int d, int l, int r) {
    int res = 0;
    for (u += N, d += N; u < d; u >>= 1, d >>= 1) {
        if (u & 1) res += t[u++].get(l, r);
        if (d & 1) res += t[--d].get(l, r);
    }
    return res;
}
void solve() {
    int n, q;
    cin >> n >> q;
    int ar[n][n];
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            ar[i][j] = s[j] == '*';
            if (ar[i][j])
                update(i, j, 1);
        }
    }
    for (int i = 0; i < q; ++i) {
        int flag;
        cin >> flag;
        if (flag == 1) {
            int y, x;
            cin >> y >> x;
            y--, x--;
            int add = ar[y][x] ? -1 : 1;
            ar[y][x] += add;
            update(y, x, add);
        } else if (flag == 2) {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            y1--, x1--;
            cout << get(y1, y2, x1, x2) << '\n';
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
    solve();
    return 0;
}