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
    vector<int> a(n);
    for (int& el : a) cin >> el;
    int L = 0;
    while ((1 << L) < n) ++L;
    a.resize(1 << L);
    for (int bit = 0; bit < L; ++bit) {
        for (int i = 0; i < (1 << L); ++i) {
            if (i >> bit & 1) {
                a[i] ^= a[i ^ (1 << bit)];
            }
        }
    }
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
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
