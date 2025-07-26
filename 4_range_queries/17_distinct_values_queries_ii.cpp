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

const int INF = 1e9 + 7;

struct ST {
    int N = 1;
    vector<int> t;

    explicit ST(const vector<int>& a) {
        while (N < sz(a)) N <<= 1;
        t.resize(N << 1, INF);
        copy(all(a), t.begin() + N);
        for (int i = N - 1; i > 0; --i) t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    int get(int l, int r) {
        int res = INF;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }

    void update(int pos, int x) {
        t[pos += N] = x;
        for (pos >>= 1; pos > 0; pos >>= 1) t[pos] = min(t[pos << 1], t[pos << 1 | 1]);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), xx;
    for (int& el : a) {
        cin >> el;
        xx.emplace_back(el);
    }
    vector<array<int, 3>> queries(q);
    for (auto& arr : queries) {
        for (int& el : arr) cin >> el;
        --arr[1];
        if (arr[0] == 1) xx.emplace_back(arr[2]);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    for (int& el : a) el = lower_bound(all(xx), el) - xx.begin();
    for (auto& arr : queries) {
        if (arr[0] == 1) arr[2] = lower_bound(all(xx), arr[2]) - xx.begin();
    }
    int c = sz(xx);
    vector<set<int>> pos(c);
    for (int i = 0; i < n; ++i) pos[a[i]].emplace(i);
    vector<int> nxt(n, n);
    {
        vector<int> tmp(c, n);
        for (int i = n - 1; i >= 0; --i) {
            nxt[i] = tmp[a[i]];
            tmp[a[i]] = i;
        }
    }
    ST st(nxt);

    for (auto [tp, s, t] : queries) {
        if (tp == 1) {
            int val = a[s];
            if (val == t) continue;
            {
                auto it = pos[val].lower_bound(s);
                if (it != pos[val].begin()) {
                    auto nx_it = next(it);
                    int nx = nx_it == pos[val].end() ? n : *nx_it;
                    int pr = *prev(it);
                    st.update(pr, nx);
                    nxt[pr] = nx;
                }
                pos[val].erase(it);
            }
            {
                auto [it, _] = pos[t].emplace(s);
                auto nx_it = next(it);
                int nx = nx_it == pos[t].end() ? n : *nx_it;
                st.update(s, nx);
                nxt[s] = nx;
                if (it != pos[t].begin()) {
                    int pr = *prev(it);
                    st.update(pr, s);
                    nxt[pr] = s;
                }
            }
            a[s] = t;
        } else {
            cout << (st.get(s, t) >= t ? "YES" : "NO") << '\n';
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
