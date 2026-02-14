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

const int K = 26;
const int N = 3000;
int pos[K][N][N];
int cnt[K][N];

void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> field(n);
    for (auto& el : field) cin >> el;
    vector color(n, vector<int>(n, -1));
//    vector pos(k, vector(n, vector<int>()));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = field[i][j] - 'A';
            pos[x][i][cnt[x][i]++] = j;
        }
    }
    for (int x = 0; x < k; ++x) {
        bool ok = false;
        vector<int> good_i;
        for (int i = 0; i < n; ++i) {
            if (cnt[x][i] >= 2) good_i.emplace_back(i);
        }
        sort(all(good_i), [&](int i1, int i2) {
            return cnt[x][i1] < cnt[x][i2];
        });
        if (sz(good_i) > 1) {
            for (int i: good_i) {
                for (int c1 = 0; c1 < cnt[x][i]; ++c1) {
                    if (ok) break;
                    for (int c2 = c1 + 1; c2 < cnt[x][i]; ++c2) {
                        int j1 = pos[x][i][c1];
                        int j2 = pos[x][i][c2];
                        if (color[j2][j1] == x) {
                            ok = true;
                            break;
                        }
                        color[j2][j1] = x;
                    }
                }
                if (ok) break;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
//        break;
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
