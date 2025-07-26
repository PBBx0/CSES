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

struct node {
    int l = -1, r = -1;
    ll sm = 0;
};

vector<node> t;

int new_node(int l = -1, int r = -1, ll sm = 0) {
    t.emplace_back(l, r, sm);
    return sz(t) - 1;
}

int build(const vector<int>& a, int l, int r) {
    if (l + 1 == r) return new_node(-1, -1, a[l]);
    int mid = (l + r) / 2;
    int tl = build(a, l, mid), tr = build(a, mid, r);
    return new_node(tl, tr, t[tl].sm + t[tr].sm);
}

ll get_sum(int v, int tl, int tr, int l, int r) {
    if (tl >= r || tr <= l) return 0;
    if (tl >= l && tr <= r) {
        return t[v].sm;
    }
    int tm = (tl + tr) / 2;
    return get_sum(t[v].l, tl, tm, l, r) + get_sum(t[v].r, tm, tr, l, r);
}

int update(int v, int tl, int tr, int pos, int x) {
    if (tl > pos || tr <= pos) return v;
    if (tl + 1 == tr) {
        return new_node(-1, -1, x);
    }
    int tm = (tl + tr) / 2;
    int l = update(t[v].l, tl, tm, pos, x);
    int r = update(t[v].r, tm, tr, pos, x);
    return new_node(l, r, t[l].sm + t[r].sm);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> roots;
    roots.emplace_back(build(a, 0, sz(a)));
    for (int i = 0; i < q; ++i) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            --k, --a;
            roots[k] = update(roots[k], 0, n, a, x);
        } else if (tp == 2) {
            int k, l, r;
            cin >> k >> l >> r;
            --k, --l;
            cout << get_sum(roots[k], 0, n, l, r) << '\n';
        } else if (tp == 3) {
            int k;
            cin >> k;
            --k;
            roots.emplace_back(roots[k]);
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
