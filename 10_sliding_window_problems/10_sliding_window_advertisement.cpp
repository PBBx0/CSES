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

struct line {
    ll k = 0, b = -INF;

    ll operator()(ll x) const {
        return k * x + b;
    }
};


struct li_chao {
    int N = 1;
    vector<line> t;

    li_chao(int n) {
        while (N < n) N <<= 1;
        t.resize(N << 1);
    }

    void add_line(int v, int tl, int tr, line L) {
        for (;;) {
            int tm = (tl + tr) / 2;
            if (t[v](tm) < L(tm)) {
                swap(t[v], L);
            }
            if (tl + 1 == tr || t[v].k == L.k) break;
            if (t[v].k > L.k) {
                v = v << 1 | 0;
                tr = tm;
            } else {
                v = v << 1 | 1;
                tl = tm;
            }
        }
    }

    void add_line(int l, int r, line L) {
        int lb = l, rb = r, len = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (l & 1) {
                add_line(l, lb, lb + len, L);
                ++l;
                lb += len;
            }
            if (r & 1) {
                --r;
                add_line(r, rb - len, rb, L);
                rb -= len;
            }
        }
    }

    ll get(int x) {
        ll res = -INF;
        for (int v = x + N; v > 0; v >>= 1) res = max(res, t[v](x));
        return res;
    }

};

struct seg {
    int l, r;
    ll val;
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    vector<int> lft(n, -1), rgt(n, n), s;
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && a[s.back()] > a[i]) {
            rgt[s.back()] = i;
            s.pop_back();
        }
        lft[i] = s.empty() ? -1
                : a[s.back()] == a[i] ? lft[s.back()]
                : s.back();
        s.emplace_back(i);
    }
    vector<seg> segments;
    for (int i = 0; i < n; ++i) {
        segments.emplace_back(lft[i] + 1, rgt[i], 1LL * a[i] * (rgt[i] - lft[i] - 1));
    }
    vector<vector<int>> l_idx(n), r_idx(n);
    for (int i = 0; i < sz(segments); ++i) {
        auto [l, r, val] = segments[i];
        l_idx[l].emplace_back(i);
        r_idx[r - 1].emplace_back(i);
    }

    li_chao left_bound(n), right_bound(n);
    for (int i = 0; i < n; ++i) {
        int j = rgt[i] - 1;
        int l = max(j - k, lft[i]) + 1;
        left_bound.add_line(l, j + 1, {-a[i], 1LL * (j + 1) * a[i]});

        j = lft[i] + 1;
        int r = min(j + k, rgt[i]);
        right_bound.add_line(j, r, {a[i], -1LL * (j - 1) * a[i]});
    }


    set<pair<ll, int>> inner;
    deque<int> mn_idx;
    for (int i = 0; i < n; ++i) {
        while (!mn_idx.empty() && a[mn_idx.back()] >= a[i]) mn_idx.pop_back();
        mn_idx.emplace_back(i);

        for (int id : r_idx[i]) {
            auto [l, r, val] = segments[id];
            if (l >= i - k) {
                inner.emplace(val, id);
            }
        }
        if (i >= k) {
            for (int id : l_idx[i - k]) {
                auto [l, r, val] = segments[id];
                inner.erase({val, id});
            }
            if (!mn_idx.empty() && mn_idx.front() == i - k) mn_idx.pop_front();
        }
        if (i >= k - 1) {
            ll ans = inner.empty() ? -INF : inner.rbegin()->first;
            ans = max(ans, right_bound.get(i));
            ans = max(ans, left_bound.get(i - k + 1));
            ans = max(ans, (ll)k * a[mn_idx.front()]);
            cout << ans << ' ';
        }
    }
    cout << '\n';
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
