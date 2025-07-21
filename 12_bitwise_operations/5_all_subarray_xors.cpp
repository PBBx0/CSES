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

const int LOG = 20;

void hadamard(vector<ll>& x, bool inverse) {
    for (int l = 0; l < LOG; ++l) {
        for (int mask = 0; mask < (1 << LOG); ++mask) {
            if (~mask >> l & 1) {
                ll u = x[mask], v = x[mask | 1 << l];
                x[mask] = (u + v) >> inverse;
                x[mask | 1 << l] = (u - v) >> inverse;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> x(1 << LOG), ans;
    int p = 0;
    ++x[p];
    for (int i = 0; i < n; ++i) {
        p ^= a[i];
        if (x[p] && ans.empty()) ans.emplace_back(0);
        ++x[p];
    }

    hadamard(x, false);
    for (int i = 0; i < (1 << LOG); ++i) {
        x[i] *= x[i];
    }
    hadamard(x, true);
    for (int i = 1; i < (1 << LOG); ++i) {
        if (x[i]) ans.emplace_back(i);
    }
    cout << sz(ans) << '\n';
    for (ll el : ans) cout << el << ' ';
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
