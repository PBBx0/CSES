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

ll ans = 0;
int lo = 0, hi = 0;
const int N = 2e5;
vector<int> g[N];
struct DS {
    vector<int> v = {0, 1};
    int & operator[](int i) {
        return v[sz(v) - i - 1];
    }
    void extend() { v.push_back(v.back()); }
    int size() { return v.size() - 1; }
    ll ask(int l, int r) {
        if (r <= 0 || l >= size()) return 0;
        l = max(l, 0), r = min(r, size());
        return (*this)[l] - (*this)[r];
    }
    void merge(DS & other) {
        if (size() < other.size()) swap(*this, other);
        for (int i = 0; i < other.size(); ++i) {
            int l = lo - i, r = hi - i;
            ans += ask(l, r) * (other[i] - other[i + 1]);
        }
        for (int i = 0; i < other.size(); ++i) {
            (*this)[i] += other[i];
        }
        other.v.clear();
    }
};
DS ds[N];
void dfs(int v, int p) {
    for (int to : g[v]) if (to != p) {
            dfs(to, v);
            ds[to].extend();
            ds[v].merge(ds[to]);
        }
}
void solve() {
    int n;
    cin >> n >> lo >> hi;
    hi++;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(0, 0);
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
