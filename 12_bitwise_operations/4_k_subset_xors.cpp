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
                if (!a[l]) return a[l] = x, true;
                x ^= a[l];
            }
        }
        return false;
    }

    int get_next(int x) {
        for (int l = 0; l < LOG; ++l) {
            if ((~x >> l & 1) && a[l] != 0) {
                x ^= a[l];
                for (int j = l - 1; j >= 0; --j) {
                    if (x >> j & 1) x ^= a[j];
                }
                return x;
            }
        }
        return 0;
    }

    int get_cnt() {
        int res = 0;
        for (int l = 0; l < LOG; ++l) res += a[l] != 0;
        return res;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    xor_basis basis;
    for (int el : a) basis.insert(el);
    int cnt = n - basis.get_cnt();
    if (cnt >= 20) {
        for (int i = 0; i < k; ++i) {
            cout << 0 << ' ';
        }
        cout << '\n';
        return;
    }
    cnt = 1 << cnt;
    int x = 0;
    int cur = 0;
    for (int i = 0; i < k; ++i) {
        if (cur == cnt) {
            cur = 0, x = basis.get_next(x);
        }
        ++cur;
        cout << x << ' ';
    }
    cout << '\n';
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
