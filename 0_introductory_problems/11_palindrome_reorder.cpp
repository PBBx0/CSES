#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

using ll = int64_t;

void solve() {
    string s;
    cin >> s;
    const int C = 26;
    array<int, C> cnt{};
    for (char x : s) ++cnt[x - 'A'];
    string a;
    char b = '0';
    for (int i = 0; i < C; ++i) {
        for (int j = 0; j < cnt[i] / 2; ++j) a += char('A' + i);
        if (cnt[i] & 1) {
            if (b != '0') {
                cout << "NO SOLUTION\n";
                return;
            }
            b = char('A' + i);
        }
    }
    cout << a;
    if (b != '0') cout << b;
    reverse(all(a));
    cout << a << '\n';
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