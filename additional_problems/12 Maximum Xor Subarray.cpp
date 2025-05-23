#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int LOG = 30;
struct node {
    int l = -1, r = -1;
    node(){}
};
vector<node> t(1);
void add_num(int x) {
    int v = 0;
    for (int i = LOG; i >= 0; --i) {
        if (x & (1 << i)) {
            if (t[v].r == -1) {
                t[v].r = sz(t);
                t.emplace_back();
            }
            v = t[v].r;
        } else {
            if (t[v].l == -1) {
                t[v].l = sz(t);
                t.emplace_back();
            }
            v = t[v].l;
        }
    }
}
int get(int x) {
    int res = 0;
    int v = 0;
    for (int i = LOG; i >= 0; --i) {
        if (x & (1 << i)) {
            if (t[v].l != -1) {
                res += (1 << i);
                v = t[v].l;
            } else {
                v = t[v].r;
            }
        } else {
            if (t[v].r != -1) {
                res += (1 << i);
                v = t[v].r;
            } else {
                v = t[v].l;
            }
        }
    }
    return res;
}
void solve() {
    add_num(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & i : a) cin >> i;
    int x = 0, res = 0;
    for (int i : a) {
        x ^= i;
        res = max(res, get(x));
        add_num(x);
    }
    cout << res << '\n';
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