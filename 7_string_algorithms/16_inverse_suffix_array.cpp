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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), sa(n + 1);
    for (int& el : a) cin >> el, --el;
    for (int i = 0; i < n; ++i) {
        sa[a[i]] = i;
    }
    sa[n] = -1;
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[sa[i]] = i;
    }
    char letter = 'a';
    vector<char> ans(n);
    int last = -1;
    for (int p : pos) {
        if (last != -1 && sa[last + 1] > sa[p + 1]) {
            ++letter;
        }
        if (letter > 'z') {
            cout << -1 << '\n';
            return;
        }
        ans[p] = letter;
        last = p;
    }
    for (char el : ans) cout << el;
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
