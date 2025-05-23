#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
using ll = int64_t;
struct node {
    node *l = nullptr, *r = nullptr;
    int sz = 1;
    ll sum, x;
    bool rev = false;
    node(ll x) : x(x), sum(x) {}
};
using pnode = node*;
void push(pnode t) {
    if (!t->rev) return;
    if (t->l) t->l->rev ^= true;
    if (t->r) t->r->rev ^= true;
    swap(t->l, t->r);
    t->rev = false;
}
int get_sz(pnode t) {
    return t ? t->sz : 0;
}
ll get_sm(pnode t) {
    return t ? t->sum : 0;
}
pnode recalc(pnode t) {
    t->sz = get_sz(t->l) + 1 + get_sz(t->r);
    t->sum = get_sm(t->l) + t->x + get_sm(t->r);
    return t;
}
pnode merge(pnode t1, pnode t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    if (rnd() % (t1->sz + t2->sz) < t1->sz) {
        push(t1);
        t1->r = merge(t1->r, t2);
        return recalc(t1);
    } else {
        push(t2);
        t2->sz += t1->sz;
        t2->l = merge(t1, t2->l);
        return recalc(t2);
    }
}

pair<pnode, pnode> split(pnode t, int k) {
    if (t == nullptr) return {nullptr, nullptr};
    push(t);
    if (get_sz(t->l) >= k) {
        auto [t1, t2] = split(t->l, k);
        t->l = t2;
        return {t1, recalc(t)};
    } else {
        auto [t1, t2] = split(t->r, k - 1 - get_sz(t->l));
        t->r = t1;
        return {recalc(t), t2};
    }
}
void solve() {
    int n, q;
    cin >> n >> q;
    pnode root = nullptr;
    for (int i = 0; i < n; ++ i) {
        int x;
        cin >> x;
        root = merge(root, new node(x));
    }
    for (int i = 0; i < q; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;
        auto [tmp, t3] = split(root, r);
        auto [t1, t2] = split(tmp, l);
        if (t == 1) {
            t2->rev ^= true;
        } else {
            cout << get_sm(t2) << '\n';
        }
        root = merge(t1, merge(t2, t3));
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