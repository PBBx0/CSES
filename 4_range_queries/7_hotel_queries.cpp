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

struct ST {
    int N = 1;
    vector<int> t;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i)
            t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void upd(int pos, int x) {
        t[pos += N] = x;
        for (pos >>= 1; pos > 0; pos >>= 1) t[pos] = max(t[pos << 1], t[pos << 1 | 1]);
    }

    int lower_bound(int x) {
        int v = 1;
        if (t[v] < x) return -1;
        while (v < N) {
            if (t[v << 1] >= x) v = v << 1;
            else v = (v << 1) | 1;
        }
        return v - N;
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    ST st(a);
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        int p = st.lower_bound(x);
        cout << p + 1 << ' ';
        if (p != -1) {
            a[p] -= x;
            st.upd(p, a[p]);
        }
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
