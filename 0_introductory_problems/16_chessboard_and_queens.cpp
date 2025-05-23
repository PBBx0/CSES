#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    const int D = 8;
    vector<string> field(D);
    for (auto& el : field) cin >> el;
    vector banned(D, vector<bool>(D));
    for (int i = 0; i < D; ++i) for (int j = 0; j < D; ++j) banned[i][j] = field[i][j] == '*';
    vector<int> perm(D);
    iota(all(perm), 0);
    int ans = 0;
    do {
        bool ok = true;
        for (int i = 0; i < D; ++i) if (banned[i][perm[i]]) {
            ok = false;
            break;
        }
        if (!ok) continue;
        for (int i = 0; i < D; ++i) {
            for (int j = i + 1; j < D; ++j) {
                if (abs(perm[j] - perm[i]) == j - i) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        ans += ok;
    } while (next_permutation(all(perm)));
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
//    cout << fixed << setprecision(20);
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}