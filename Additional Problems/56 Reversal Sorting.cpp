#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
struct node {
    node *l = nullptr, *r = nullptr;
    int mi, x, sz = 1;
    bool rev = false;
    node(int x) : mi(x), x(x) {}
};
const int INF = 1e9 + 1000 - 7;
using pnode = node*;
int get_mi(pnode t) {
    return t != nullptr ? t->mi : INF;
}
int get_sz(pnode t) {
    return t != nullptr ? t->sz : 0;
}
void push(pnode t) {
    if (!t->rev) return;
    if (t->l != nullptr) t->l->rev ^= true;
    if (t->r != nullptr) t->r->rev ^= true;
    t->rev = false;
    swap(t->l, t->r);
}
void recalc(pnode t) {
    t->sz = get_sz(t->l) + 1 + get_sz(t->r);
    t->mi = min({get_mi(t->l), t->x, get_mi(t->r)});
}
pnode merge(pnode t1, pnode t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    if (rnd() % (t1->sz + t2->sz) < t1->sz) {
        push(t1);
        t1->r = merge(t1->r, t2);
        recalc(t1);
        return t1;
    } else {
        push(t2);
        t2->l = merge(t1, t2->l);
        recalc(t2);
        return t2;
    }
}
pair<pnode, pnode> split(pnode t, int k) {
    if (t == nullptr) return {nullptr, nullptr};
    push(t);
    if (get_sz(t->l) >= k) {
        auto [t1, t2] = split(t->l, k);
        t->l = t2;
        recalc(t);
        return {t1, t};
    } else {
        auto [t1, t2] = split(t->r, k - get_sz(t->l) - 1);
        t->r = t1;
        recalc(t);
        return {t, t2};
    }
}
int get_pos(pnode t) {
    push(t);
    int mi = t->mi;
    if (mi == t->x) return get_sz(t->l);
    if (get_mi(t->l) == mi) return get_pos(t->l);
    else return get_sz(t->l) + 1 + get_pos(t->r);
}
void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int & el : a) {cin >> el; --el;}
    pnode root = nullptr;
    for (int el : a) root = merge(root, new node(el));
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int p = get_pos(root);
        cout << i + 1 << ' ' << i + p + 1 << '\n';
        auto [tmp, t3] = split(root, p + 1);
        tmp->rev ^= true;
        auto [t1, t2] = split(tmp, 1);
        root = merge(t2, t3);
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
    solve();
    return 0;
}