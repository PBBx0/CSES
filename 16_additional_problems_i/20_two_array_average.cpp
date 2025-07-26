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



void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (ll& el : a) cin >> el;
    for (ll& el : b) cin >> el;

    vector<ll> pa(n + 1), pb(n + 1);
    for (int i = 0; i < n; ++i) {
        pa[i + 1] = pa[i] + a[i];
        pb[i + 1] = pb[i] + b[i];
    }

    int best1 = 1, best2 = 1;
    auto relax = [&](int i, int j) {
        ll sm = pa[i] + pb[j];
        ll len = i + j;
        ll sm2 = pa[best1] + pb[best2];
        ll len2 = best1 + best2;
        if (sm * len2 > sm2 * len) {
            best1 = i, best2 = j;
        }
    };
    vector<int> rb(n + 1);
    rb[n] = n;

    auto better_avg = [&](int l, int mid, int r) {
        ll sm1 = pa[mid] - pa[l];
        ll sm2 = pa[r] - pa[mid];
        ll len1 = mid - l;
        ll len2 = r - mid;
        return sm2 * len1 >= sm1 * len2;
    };

    for (int l = n - 1; l >= 0; --l) {
        int t = l + 1;
        while (t < n && better_avg(l, t, rb[t])) t = rb[t];
        rb[l] = t;
    }

    auto better_avg2 = [&](int i, int l, int mid, int r) {
        ll sm1 = pa[mid] - pa[l] + pb[i];
        ll sm2 = pa[r] - pa[mid];
        ll len1 = mid - l + i;
        ll len2 = r - mid;
        return sm2 * len1 >= sm1 * len2;
    };

    for (int i = 1; i <= n; ++i) {
        int t = 1;
        while (t < n && better_avg2(i, 0, t, rb[t])) t = rb[t];
        relax(t, i);
    }


    cout << best1 << ' ' << best2 << '\n';
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
