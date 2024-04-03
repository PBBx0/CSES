#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 20, M = 1 << N;
int cnt[M], sub[M], bus[M];
void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int & el : a) {
        cin >> el;
        cnt[el]++;
    }
    for (int i = 0; i < M; ++i) sub[i] = bus[i] = cnt[i];
    for (int i = 0; i < N; ++i) {
        for (int mask = 0; mask < M; ++mask) {
            if (mask & (1 << i)) sub[mask] += sub[mask ^ (1 << i)];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int mask = M - 1; mask >= 0; --mask) {
            if ((mask & (1 << i)) == 0) bus[mask] += bus[mask ^ (1 << i)];
        }
    }
    for (int x : a) {
        cout << sub[x] << ' ' << bus[x] << ' ' << n - sub[M - x - 1] << '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
    return 0;
}