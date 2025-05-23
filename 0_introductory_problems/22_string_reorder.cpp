#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    string str;
    cin >> str;
    const int C = 26;
    array<int, C> cnt{};
    for (char x : str) ++cnt[x - 'A'];
    const int len = sz(str);
    if (*max_element(all(cnt)) > (len + 1) / 2) {
        cout << -1 << '\n';
        return;
    }
    string out;
    int last = -1;
    for (int i = 0; i < sz(str); ++i) {
        bool placed = false;
        for (int d = 0; d < C; ++d) {
            if (cnt[d] > (len - i) / 2) {
                last = d;
                out += char(d + 'A');
                --cnt[d];
                placed = true;
                break;
            }
        }
        if (placed) continue;
        for (int d = 0; d < C; ++d) {
            if (d != last && cnt[d] > 0) {
                last = d;
                out += char(d + 'A');
                --cnt[d];
                placed = true;
                break;
            }
        }
    }
    cout << out << '\n';
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