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

const int LOG = 19;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& el : a) cin >> el;

    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];

//    vector<int> lb(n + 1);

    auto better_average = [&](int l, int mid, int r) {
        ll sm1 = pref[mid] - pref[l];
        ll len1 = mid - l;
        ll sm2 = pref[r] - pref[mid];
        ll len2 = r - mid;
        return sm1 * len2 >= sm2 * len1;
    };
    vector bj(LOG, vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        int r = i + 1;
        int t = i;
        for (int l = LOG - 1; l >= 0; --l) {
            int s = bj[l][t];
            if (s > 0 && better_average(bj[0][s], s, r)) {
                t = s;
            }
        }
        if (t > 0 && better_average(bj[0][t], t, r)) {
            t = bj[0][t];
        }
        bj[0][r] = t;
        for (int l = 1; l < LOG; ++l) {
            bj[l][r] = bj[l - 1][bj[l - 1][r]];
        }
    }
    for (int r = 1; r <= n; ++r) {
        cout << r - bj[0][r] << ' ';
    }
    cout << '\n';
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
