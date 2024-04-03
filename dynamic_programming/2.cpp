#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
constexpr int A = 1e6 + 73;
int d[A];
void solve() {
    fill(d, d + A, -1);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (int& el : c) cin >> el;
    d[0] = 0;
    for (int el : c) {
        for (int i = 0; i + el <= x; ++i) if (d[i] != -1) {
            if (d[i + el] == -1 || d[i + el] > d[i] + 1) {
                d[i + el] = d[i] + 1;
            }
        }
    }
    cout << d[x] << '\n';
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