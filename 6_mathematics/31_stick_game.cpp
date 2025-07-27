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
    int n, k;
    cin >> n >> k;
    vector<int> moves(k);
    for (int& el : moves) cin >> el;
    sort(all(moves));
    vector<bool> win(n + 1);
    win[0] = false;
    for (int i = 1; i <= n; ++i) {
        win[i] = false;
        for (int d : moves) {
            if (i - d < 0) break;
            if (!win[i - d]) {
                win[i] = true;
                break;
            }
        }
        cout << "LW"[win[i]];
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
