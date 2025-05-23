#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const ll INF = 1e18;
const int N = 3000;
struct FT {
    ll t[N]{};
    ll get(ll p) {
        ll res = 0;
        for (; p > 0; p &= p - 1) res += t[p - 1];
        return res;
    }
    void update(ll p, ll x) {
        for (; p < N; p |= p + 1) t[p] += x;
    }
    void clear() {
        fill(t, t + N, 0);
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int & el : a) cin >> el;
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, INF)), \
    cost(n + 1, vector<ll>(n + 1)), opt(n + 2, vector<ll>(k + 1));
    FT ft_sum, ft_prod;
    for (int l = 0; l < n; ++l) {
        ft_sum.clear(), ft_prod.clear();
        int m = l;
        ll all_sm = 0;
        for (int r = l; r < n; ++r) {
            all_sm += a[r];
            ft_sum.update(r, a[r]);
            ft_prod.update(r, 1LL * r * a[r]);
            while (ft_sum.get(m + 1) * 2 < all_sm) m++;
            ll sum1 = ft_sum.get(m), prod1 = ft_prod.get(m);
            ll sum2 = ft_sum.get(r + 1), prod2 = ft_prod.get(r + 1);
            sum2 -= sum1, prod2 -= prod1;
            cost[l][r + 1] = m * sum1 - prod1 + prod2 - m * sum2;
        }
    }
    dp[0][0] = 0;
    for (int j = 1; j <= k; ++j) {
        opt[n + 1][j] = n - 1;
        for (int i = n; i >= 0; --i) {
            for (ll p = opt[i][j - 1]; p <= opt[i + 1][j]; ++p) {
                ll cur = dp[p][j - 1] + cost[p][i];
                if (dp[i][j] > cur) {
                    dp[i][j] = cur;
                    opt[i][j] = p;
                }
            }
        }
    }
    cout << dp[n][k] << '\n';
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