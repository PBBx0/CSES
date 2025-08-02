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

const ll INF = 2e18;

const int LOG = 19;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll& el : a) cin >> el;
    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
    vector<int> nx(n + 1, n);
    int r = 0;
    ll cur = 0;
    for (int i = 0; i < n; ++i) {
        while (r < n && cur + a[r] <= k) {
            cur += a[r];
            ++r;
        }
        nx[i] = r;
        cur -= a[i];
    }
    vector bj(LOG, vector<int>(n + 1));
    bj[0] = nx;
    for (int l = 1; l < LOG; ++l) {
        for (int i = 0; i <= n; ++i) {
            bj[l][i] = bj[l - 1][bj[l - 1][i]];
        }
    }
    int ans = n;
    for (int i = 0; i < n; ++i) {
        if (pref[i] > k) break;
        int cnt = 1, j = i;
        for (int l = LOG - 1; l >= 0; --l) {
            if (bj[l][j] < n) {
                cnt += 1 << l;
                j = bj[l][j];
            }
        }
        ll pr = pref[i], sf = pref[n] - pref[j];
        if (pr + sf > k) ++cnt;
        ans = min(ans, cnt);
    }
    cout << ans << '\n';
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
