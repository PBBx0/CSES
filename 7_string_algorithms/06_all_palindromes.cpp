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

template<int C> struct EERTREE {
    int top = 1, last = 0, sz = 2;
    vector<int> str, suff, len;
    vector<array<int, C>> nx;

    EERTREE(int n) : str(n + 1, -1), suff(n + 2)
            , len(n + 2), nx(n + 2, array<int, C>()) {
        len[1] = -1, suff[0] = 1;
    }
    int get_link(int v) {
        while (str[top - len[v] - 2] != str[top - 1]) v = suff[v];
        return v;
    }
    void add_letter(int c) {
        str[top++] = c;
        last = get_link(last);
        if (!nx[last][c]) {
            len[sz] = len[last] + 2;
            suff[sz] = nx[get_link(suff[last])][c];
            nx[last][c] = sz++;
        }
        last = nx[last][c];
    }
};

void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    EERTREE<26> tree(n);
    for (int i = 0; i < n; ++i) {
        tree.add_letter(s[i] - 'a');
        cout << tree.len[tree.last] << ' ';
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
