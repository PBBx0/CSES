#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
void solve() {
    int n;
    cin >> n;
    int a[2][n];
    for (auto & ar : a) for (int & el : ar) cin >> el;
    ll ans = 0, b1 = 0, b2 = 0;
    deque<int> fst, snd;
    int p1 = 0, p2 = 0;
    for (int i = 0; i < n; ++i) {
        while (b1 < 0 && a[0][i] > 1) {
            ans += i - fst.front();
            fst.pop_front();
            a[0][i]--;
            b1++;
        }
        while (b2 < 0 && a[1][i] > 1) {
            ans += i - snd.front();
            snd.pop_front();
            a[1][i]--;
            b2++;
        }
        if (b1 > 0 && a[0][i] == 0) {
            while (a[0][p1] <= 1) ++p1;
            ans += i - p1;
            a[0][p1]--;
            a[0][i]++;
            b1--;
        }
        if (b2 > 0 && a[1][i] == 0) {
            while (a[1][p2] <= 1) ++p2;
            ans += i - p2;
            a[1][p2]--;
            a[1][i]++;
            b2--;
        }

        if (a[0][i] == 0) fst.emplace_back(i);
        if (a[1][i] == 0) snd.emplace_back(i);
        b1 += a[0][i] - 1;
        b2 += a[1][i] - 1;
        while (b1 > 0 && b2 < 0) {
            while (a[0][p1] <= 1) ++p1;
            a[0][p1]--;
            ans += 1 + abs(snd.front() - p1);
            snd.pop_front();
            b1--, b2++;
        }
        while (b1 < 0 && b2 > 0) {
            while (a[1][p2] <= 1) ++p2;
            a[1][p2]--;
            ans += 1 + abs(fst.front() - p2);
            fst.pop_front();
            b1++, b2--;
        }
    }
    cout << ans << '\n';
}

signed main() {
    int tt = 1;
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    cin >> tt;
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    while (tt--) solve();
    return 0;
}
