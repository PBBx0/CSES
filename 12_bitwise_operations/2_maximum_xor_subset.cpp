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

const int LOG = 30;

struct xor_basis {
    array<int, LOG> a{};

    bool insert(int x) {
        for (int l = LOG - 1; l >= 0; --l) {
            if (x >> l & 1) {
                if (a[l] == 0) return a[l] = x, true;
                x ^= a[l];
            }
        }
        return false;
    }

    int get_max() {
        int res = 0;
        for (int l = LOG - 1; l >= 0; --l) {
            if (~res >> l & 1) {
                res ^= a[l];
            }
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    xor_basis basis;
    for (int el : a) basis.insert(el);
    cout << basis.get_max() << '\n';
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
