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

const int LOG = 30;
vector<array<int, 2>> trie(1);

void add_num(int x) {
    int v = 0;
    for (int l = LOG - 1; l >= 0; --l) {
        int bit = x >> l & 1;
        if (!trie[v][bit]) {
            trie[v][bit] = sz(trie);
            trie.emplace_back();
        }
        v = trie[v][bit];
    }
}

int max_query(int x) {
    int v = 0;
    int ans = 0;
    for (int l = LOG - 1; l >= 0; --l) {
        int bit = ~x >> l & 1;
        if (trie[v][bit]) {
            ans |= 1 << l;
        } else {
            bit ^= 1;
        }
        v = trie[v][bit];
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;
    int cur = 0;
    add_num(cur);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cur ^= a[i];
        ans = max(ans, max_query(cur));
        add_num(cur);
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
