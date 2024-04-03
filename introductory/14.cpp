#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
vector<pair<int, int>> out;
int third(int a, int b) {
    return 6 - a - b;
}
void move(int fst, int snd, int n) {
    if (n == 1) {
        out.emplace_back(fst, snd);
        return;
    }
    int t = third(fst, snd);
    move(fst, t, n - 1);
    move(fst, snd, 1);
    move(t, snd, n - 1);
}
void solve() {
    int n;
    cin >> n;
    move(1, 3, n);
    cout << sz(out) << '\n';
    for (auto [a, b] : out) {
        cout << a << ' ' << b << '\n';
    }
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