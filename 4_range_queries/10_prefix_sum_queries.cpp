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

const ll INF = 1e18;

struct ST {
    int N = 1;
    vector<ll> t;
    vector<ll> add;

    explicit ST(const vector<ll>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1, -INF);
        add.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = max(t[i << 1], t[i << 1 | 1]);
    }

    void update(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        update(v << 1 | 0, tl, tm, l, r, x);
        update(v << 1 | 1, tm, tr, l, r, x);
        t[v] = max(t[v << 1 | 0] + add[v << 1 | 0],
                   t[v << 1 | 1] + add[v << 1 | 1]);
    }

    void update(int l, int r, int x) {
        update(1, 0, N, l, r, x);
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return -INF;
        if (tl >= l && tr <= r) return t[v] + add[v];
        int tm = (tl + tr) / 2;
        return add[v] + max(get(v << 1 | 0, tl, tm, l, r),
                            get(v << 1 | 1, tm, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<ll> p(n + 1);
    for (int i = 0; i < n; ++i) p[i + 1] = p[i] + a[i];
    ST st(p);
    for (int i = 0; i < q; ++i) {
        int tp, s, t;
        cin >> tp >> s >> t;
        --s;
        if (tp == 1) {
            int delta = t - a[s];
            a[s] += delta;
            st.update(s + 1, n + 1, delta);
        } else {
            cout << st.get(s, t + 1) - st.get(s, s + 1) << '\n';
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
    int tt = 1;
//    cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
