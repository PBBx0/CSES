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

    vector<vector<int>> ans(9);
    vector<bool> has_ans(9);
    ans[1] = {1};
    has_ans[1] = true;
    for (int len = 4; len <= 8; ++len) {
        has_ans[len] = true;
        auto& vec = ans[len];
        vec.resize(len);
        iota(all(vec), 1);
        do {
            bool ok = true;
            for (int i = 1; i < len; ++i) {
                if (abs(vec[i] - vec[i - 1]) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) break;
        } while (next_permutation(all(vec)));
    }

    int n;
    cin >> n;
    if (n < 9 && !has_ans[n]) {
        cout << "NO SOLUTION\n";
        return;
    }
    vector<int> outp(n);
    auto ptr = outp.data();
    int add = 0;
    int m = n;
    while (m >= 9) {
        for (int j = 0; j < 5; ++j) ptr[j] = add + ans[5][j];
        m -= 5;
        add += 5;
        ptr += 5;
    }
    for (int j = 0; j < m; ++j) ptr[j] = add + ans[m][j];
    for (int el : outp) cout << el << ' ';
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
