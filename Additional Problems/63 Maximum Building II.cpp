#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
struct ST {
    int N = 1;
    vector<int> ph, t;
    ST(int n) {
        for (; N < n; N <<= 1);
        ph.resize(N << 1), t.resize(N << 1);
    }
    int get_m(int v) {
        return ph[v] ? ph[v] : t[v];
    }
    void push(int v) {
        if (ph[v] == 0) return;
        t[v] = ph[v + v] = ph[v + v + 1] = ph[v];
        ph[v] = 0;
    }
    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            ph[v] = x;
            return;
        }
        int tm = (tr - tl) / 2 + tl;
        push(v);
        update(v + v, tl, tm, l, r, x), update(v + v + 1, tm, tr, l, r, x);
        t[v] = min(get_m(v + v), get_m(v + v + 1));
    }
    int get(int p) {
        int res = get_m(p += N);
        for (p >>= 1; p > 0; p >>= 1) {
            if (ph[p]) res = ph[p];
        }
        return res;
    }
};
const int N = 1010;
int ar[N][N], dp[N], rt[N], lt[N];
ll cnt[N][N];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char t;
            cin >> t;
            ar[i][j] = t == '.';
        }
    }
    vector<int> st;
    ST f(N);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) dp[j] = ar[i][j] ? dp[j] + 1 : 0;
        fill(rt, rt + m, m);
        fill(lt, lt + m, -1);
        st.clear();
        for (int j = 0; j < m; ++j) {
            while (!st.empty() && dp[st.back()] > dp[j]) {
                rt[st.back()] = j;
                st.pop_back();
            }
            if (!st.empty()) {
                lt[j] = dp[j] == dp[st.back()] ? lt[st.back()] : st.back();
            }
            st.push_back(j);
        }
        f.ph[1] = -1;
        for (int j = 0; j < m; ++j) {
            if (f.get(dp[j]) > j) continue;
            int r = rt[j];
            int x = r == n ? 0 : dp[r];
            int y = lt[j] == -1 ? 0 : dp[lt[j]];
            int len = r - lt[j] - 1;
            cnt[len][max(x, y) + 1]++;
            cnt[len][dp[j] + 1]--;
            f.update(1, 0, f.N, x + 1, dp[j] + 1, r);
        }
    }
    for (int a = 0; a <= m; ++a) {
        for (int x = 0; x < n; ++x) cnt[a][x + 1] += cnt[a][x];
    }
    for (int h = 1; h <= n; ++h) {
        ll cur = 0, d = 0;
        for (int len = m; len > 0; --len) {
            d += cnt[len][h];
            cur += d;
            cnt[len][h] = cur;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << cnt[j][i] << ' ';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}