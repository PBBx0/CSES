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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> submask(1 << LOG), overmask(1 << LOG);
    for (int el : a) ++submask[el], ++overmask[el];
    for (int bit = 0; bit < LOG; ++bit) {
        for (int mask = 0; mask < (1 << LOG); ++mask) {
            if (mask >> bit & 1) {
                submask[mask] += submask[mask ^ (1 << bit)];
                overmask[mask ^ (1 << bit)] += overmask[mask];
            }
        }
    }
    for (int el : a) {
        cout << submask[el] << ' ' << overmask[el] << ' ' << n - submask[~el & ((1 << LOG) - 1)] << '\n';
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
