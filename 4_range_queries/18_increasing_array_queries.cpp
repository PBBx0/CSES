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
    vector<ll> t, add;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        add.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void push(int v, int tl, int tr) {
        t[v] += add[v] * (tr - tl);
        add[v << 1 | 0] += add[v];
        add[v << 1 | 1] += add[v];
        add[v] = 0;
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return add[v] * (tr - tl) + t[v];
        int tm = (tl + tr) / 2;
        push(v, tl, tr);
        return get(v << 1 | 0, tl, tm, l, r) +
               get(v << 1 | 1, tm, tr, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, ll x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        update(v << 1 | 0, tl, tm, l, r, x);
        update(v << 1 | 1, tm, tr, l, r, x);
        t[v] += x * (min(tr, r) - max(tl, l));
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void update(int l, int r, ll x) {
        update(1, 0, N, l, r, x);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> b(n);
    for (int i = 0; i < n; ++i) b[i] = -a[i];
    ST st(b);
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i][0] >> queries[i][1];
        --queries[i][0];
        queries[i][2] = i;
    }
    vector<ll> ans(q);
    sort(all(queries));
    vector<int> s;
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && a[i] >= a[s.back()]) {
            int v = s.back();
            s.pop_back();
            int lst = s.empty() ? n : s.back();
            st.update(v, lst, -a[v]);
        }
        int lst = s.empty() ? n : s.back();
        st.update(i, lst, a[i]);
        s.emplace_back(i);

        while (!queries.empty() && queries.back()[0] == i) {
            auto [l, r, id] = queries.back();
            queries.pop_back();
            ans[id] = st.get(l, r);
        }
    }
    for (ll el : ans) cout << el << '\n';
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
