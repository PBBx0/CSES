#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
using ll = int64_t;
struct node {
    node *l = nullptr, *r = nullptr;
    char x;
    ll sz = 1;
    node(char x) : x(x) {}
};

using pnode = node*;
pnode merge(pnode t1, pnode t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    if (rnd() % (t1->sz + t2->sz) < t1->sz) {
        t1->sz += t2->sz;
        t1->r = merge(t1->r, t2);
        return t1;
    } else {
        t2->sz += t1->sz;
        t2->l = merge(t1, t2->l);
        return t2;
    }
}
int get_sz(pnode t) {
    return t == nullptr ? 0 : t->sz;
}
pair<pnode, pnode> split(pnode t, int k) {
    if (t == nullptr) return {nullptr, nullptr};
    if (get_sz(t->l) >= k) {
        auto [t1, t2] = split(t->l, k);
        t->l = t2;
        t->sz = get_sz(t->l) + 1 + get_sz(t->r);
        return {t1, t};
    } else {
        auto [t1, t2] = split(t->r, k - get_sz(t->l) - 1);
        t->r = t1;
        t->sz = get_sz(t->l) + 1 + get_sz(t->r);
        return {t, t2};
    }
}
void print(pnode t) {
    if (t == nullptr) return;
    print(t->l);
    cout << t->x;
    print(t->r);
}
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    pnode root = nullptr;
    for (char x : s) root = merge(root, new node(x));
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        auto [tmp, t3] = split(root, r);
        auto [t1, t2] = split(tmp, l);
        root = merge(merge(t1, t3), t2);
    }
    print(root);
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