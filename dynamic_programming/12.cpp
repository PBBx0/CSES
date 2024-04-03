#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1 << 20;
void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (int& el : c) cin >> el;
    bitset<N> bts;
    bts.set(0);
    for (int el : c) {
        bts |= (bts << el);
    }
    cout << bts.count() - 1 << '\n';
    for (int i = 1; i < N; ++i) {
        if (bts[i]) cout << i << ' ';
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