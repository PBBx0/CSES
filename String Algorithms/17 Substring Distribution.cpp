#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
vector<int> sa, pos, lcp;
const int M = 1e5 + 10;
void suffix_array(string & s) {
    int n = sz(s);
    vector<int> c(n), cur(n);
    sa.resize(n), pos.resize(n), lcp.resize(n);
    for (int i = 0; i < n; ++i) {
        sa[i] = i, c[i] = s[i];
    }
    sort(sa.begin(), sa.end(), [&](int i, int j) { return c[i] < c[j]; });
    int cnt[M];
    for (int k = 1; k < n; k <<= 1) {
        fill(cnt, cnt + M, 0);
        for (int x : c) cnt[x]++;
        for (int i = 1; i < M; ++i) cnt[i] += cnt[i - 1];
        for (int i : sa) {
            int c2 = c[(i - k + n) % n] - 1;
            cur[cnt[c2]++] = (i - k + n) % n;
        }
        swap(cur, sa);
        int x = -1, y = -1, p = 0;
        for (int i : sa) {
            if (c[i] != x || c[(i + k) % n] != y) {
                x = c[i], y = c[(i + k) % n], p++;
            }
            cur[i] = p;
        }
        swap(cur, c);
    }
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    int l = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            l = 0;
        } else {
            while (s[(i + l) % n] == s[(sa[pos[i] + 1] + l) % n]) ++l;
            lcp[pos[i]] = l;
            l = max(0, l - 1);
        }
    }
}
struct FT {
    vector<int> t;
    FT(int n) : t(n) {}
    int get(int p) {
        int res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }
    void update(int p) {
        for (; p < sz(t); p |= p + 1) t[p]++;
    }
};
void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    s += '#';
    suffix_array(s);
    FT ft(n + 1);
    vector<int> ans(n + 1);
    for (int i = 0; i < n; ++i) {
        int len = n - i;
        ft.update(lcp[pos[i] - 1]);
        ans[len] = ft.get(len);
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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