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

    ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1);
        add.resize(N << 1);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = t[i << 1 | 0] + t[i << 1 | 1];
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return t[v] + (tr - tl) * add[v];
        int tm = (tl + tr) / 2;
        return add[v] * (min(r, tr) - max(l, tl)) +
            get(v << 1 | 0, tl, tm, l, r) +
            get(v << 1 | 1, tm, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, N, l, r);
    }

    void upd(int v, int tl, int tr, int l, int r, ll x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            add[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        t[v] += x * (min(r, tr) - max(l, tl));
        upd(v << 1 | 0, tl, tm, l, r, x);
        upd(v << 1 | 1, tm, tr, l, r, x);
    }

    void upd(int l, int r, ll x) {
        upd(1, 0, N, l, r, x);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int& el : a) cin >> el;
    map<int, int> mp;
    vector<int> nxt(n);
    for (int i = n - 1; i >= 0; --i) {
        nxt[i] = mp.contains(a[i]) ? mp[a[i]] : n;
        mp[a[i]] = i;
    }
    set<int> s;
    vector<int> b(n);
    for (int r = 0; r < n; ++r) {
        s.emplace(a[r]);
        b[r] = sz(s);
    }
    ST st(b);
    ll ans = 0;
    for (int l = 0; l < n; ++l) {
        ans += st.get(0, n);
        st.upd(l, nxt[l], -1);
    }
    cout << ans << '\n';
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
