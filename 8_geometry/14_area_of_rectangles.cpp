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
    struct Node {
        int mn = 0, cnt_mn = 0, add = 0;
    };

    int N = 1;
    vector<Node> t;

    ST(int n) {
        while (N < n) N <<= 1;
        t.resize(N << 1);
        for (int i = 0; i < n; ++i) t[i + N].cnt_mn = 1;
        for (int i = N - 1; i > 0; --i) t[i].cnt_mn = t[i << 1 | 0].cnt_mn + t[i << 1 | 1].cnt_mn;
    }

    void pull(int v) {
        int lft = t[v << 1 | 0].mn + t[v << 1 | 0].add;
        int rgt = t[v << 1 | 1].mn + t[v << 1 | 1].add;
        t[v].mn = min(lft, rgt);
        t[v].cnt_mn = 0;
        if (t[v].mn == lft) t[v].cnt_mn += t[v << 1 | 0].cnt_mn;
        if (t[v].mn == rgt) t[v].cnt_mn += t[v << 1 | 1].cnt_mn;
    }

    void push(int v) {
        t[v].mn += t[v].add;
        t[v << 1 | 0].add += t[v].add;
        t[v << 1 | 1].add += t[v].add;
        t[v].add = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int add) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            t[v].add += add;
            return;
        }
        int tm = (tl + tr) / 2;
        //no need to push
        update(v << 1 | 0, tl, tm, l, r, add);
        update(v << 1 | 1, tm, tr, l, r, add);
        pull(v);
    }

    void update(int l, int r, int add) {
        update(1, 0, N, l, r, add);
    }

    int get() {
        return t[1].cnt_mn;
    }

};

struct ev {
    int tp, x, y1, y2;
};

const int T = 1e6;

void solve() {
    int n;
    cin >> n;
    vector<ev> a;
    a.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += T, y1 += T, x2 += T, y2 += T;
        a.emplace_back(0, x1, y1, y2);
        a.emplace_back(1, x2, y1, y2);
    }
    sort(all(a), [](auto lhs, auto rhs) {
       return lhs.x < rhs.x;
    });
    int last = 0;
    ll ans = 0;
    const int B = T + T + 2;
    ST st(B);
    for (auto [tp, x, y1, y2] : a) {
        if (x != last) {
            ans += ll(B - st.get()) * (x - last);
            last = x;
        }
        if (tp == 0) {
            st.update(y1, y2, 1);
        } else {
            st.update(y1, y2, -1);
        }
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
