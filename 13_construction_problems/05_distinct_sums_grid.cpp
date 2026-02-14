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

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;
    if (n <= 3) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> b(n);
    iota(all(b), 1);
    for (int i = 0; i < n; ++i) {
        copy(b.begin() + i, b.end(), a[i].begin());
        copy(b.begin() , b.begin() + i, a[i].begin() + n - i);
    }
    for (int& el : a[n - 1]) el = n + 1 - el;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) b[i] = a[i][j];
        sort(all(b));
        for (int i = 0; i < n; ++i) a[i][j] = b[i];
    }
    for (int i = 0; i < n; ++i) sort(all(a[i]));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << a[i][j] << ' ';
        cout << '\n';
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
