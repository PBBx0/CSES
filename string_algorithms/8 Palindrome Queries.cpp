#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll P = 533, MOD = 998244353;
const int N = 2e5;
ll pw[N];
struct ST {
    int N = 1;
    vector<ll> h, rh;
    vector<int> sz;
    ST(string & s) {
        for (; N < sz(s); N <<= 1);
        h.resize(N << 1);
        rh.resize(N << 1);
        sz.resize(N << 1, 1);
        for (int i = 0; i < sz(s); ++i) {
            h[i + N] = rh[i + N] = s[i] - 'a' + 1;
        }
        for (int i = N - 1; i > 0; --i) {
            sz[i] = sz[i + i] + sz[i + i + 1];
            h[i] = (h[i + i] * pw[sz[i + i + 1]] + h[i + i + 1]) % MOD;
            rh[i] = (rh[i + i] + rh[i + i + 1] * pw[sz[i + i]]) % MOD;
        }
    }
    void update(int p, char x) {
        p += N;
        h[p] = rh[p] = x - 'a' + 1;
        for (p >>= 1; p > 0; p >>= 1) {
            h[p] = (h[p + p] * pw[sz[p + p + 1]] + h[p + p + 1]) % MOD;
            rh[p] = (rh[p + p] + rh[p + p + 1] * pw[sz[p + p]]) % MOD;
        }
    }
    bool check(int l, int r) {
        int szl = 0, szr = 0;
        ll hl = 0, hr = 0, rhl = 0, rhr = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                hl = (hl * pw[sz[l]] + h[l]) % MOD;
                rhl = (rhl + rh[l] * pw[szl]) % MOD;
                szl += sz[l];
                l++;
            }
            if (r & 1) {
                --r;
                hr = (h[r] * pw[szr] + hr) % MOD;
                rhr = (rh[r] + rhr * pw[sz[r]]) % MOD;
                szr += sz[r];
            }
        }
        ll h1 = (hl * pw[szr] + hr) % MOD;
        ll h2 = (rhl + rhr * pw[szl]) % MOD;
        return h1 == h2;
    }
};

void solve() {
    pw[0] = 1;
    for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * P % MOD;
    int n, q;
    string s;
    cin >> n >> q >> s;
    ST st(s);
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p; char x;
            cin >> p >> x;
            st.update(--p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << (st.check(--l, r) ? "YES" : "NO") <<  '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}