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

const int T = 1e7 + 1;

pair<int, int> mem[T];

void solve() {
    fill(mem, mem + T, make_pair(-1, -1));
    for (int i = 0; i * i < T; ++i) {
        for (int j = 0; i * i + j * j < T; ++j) {
            mem[i * i + j * j] = {i, j};
        }
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        cin >> n;
        for (int j = 0; j <= n; ++j) {
            auto [a, b] = mem[j];
            auto [c, d] = mem[n - j];
            if (a == -1 || c == -1) continue;
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            break;
        }
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
    solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
