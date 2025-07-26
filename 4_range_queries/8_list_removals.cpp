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

struct FT {
    vector<int> t;

    explicit FT(int n) : t(n) {}

    void upd(int pos, int x) {
        for (; pos < sz(t); pos |= pos + 1) t[pos] += x;
    }

    int lower_bound(int sm) {
        int N = 1;
        while (N * 2 <= sz(t)) N <<= 1;
        int pos = 0;
        int sum = 0;
        for (int l = N; l > 0; l >>= 1) {
            if (pos + l <= sz(t) && sum + t[pos + l - 1] < sm) {
                pos += l;
                sum += t[pos - 1];
            }
        }
        return pos;
    }

};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    FT ft(n);
    for (int i = 0; i < n; ++i) ft.upd(i, 1);
    for (int i = 0; i < n; ++i) {
        int pos;
        cin >> pos;
        int p = ft.lower_bound(pos);
        cout << a[p] << ' ';
        ft.upd(p, -1);
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
