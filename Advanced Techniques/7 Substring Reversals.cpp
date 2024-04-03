#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
using ll = int64_t;
struct node {
    node *l = nullptr, *r = nullptr;
    char x;
    int sz = 1;
    bool rev = false;
    node(char x) : x(x) {}
};
using pnode = node*;
void push(pnode t) {
    if (!t->rev) return;
    if (t->l != nullptr) t->l->rev ^= true;
    if (t->r != nullptr) t->r->rev ^= true;
    swap(t->l, t->r);
    t->rev = false;
}
pnode merge(pnode t1, pnode t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    if (rnd() % (t1->sz + t2->sz) < t1->sz) {
        push(t1);
        t1->sz += t2->sz;
        t1->r = merge(t1->r, t2);
        return t1;
    } else {
        push(t2);
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
    push(t);
    if (get_sz(t->l) >= k) {
        t->sz -= get_sz(t->l);
        auto [t1, t2] = split(t->l, k);
        t->l = t2;
        t->sz += get_sz(t->l);
        return {t1, t};
    } else {
        t->sz -= get_sz(t->r);
        auto [t1, t2] = split(t->r, k - 1 - get_sz(t->l));
        t->r = t1;
        t->sz += get_sz(t->r);
        return {t, t2};
    }
}
void print(pnode t) {
    if (t == nullptr) return;
    push(t);
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
        t2->rev ^= true;
        root = merge(t1, merge(t2, t3));
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