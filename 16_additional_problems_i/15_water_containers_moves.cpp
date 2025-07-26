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

string moves[] = {
        "FILL A",
        "FILL B",
        "EMPTY A",
        "EMPTY B",
        "MOVE A B",
        "MOVE B A",
};

void solve() {
    int A, B, x;
    cin >> A >> B >> x;
    vector dst(A + 1, vector<ll>(B + 1, INF));
    dst[0][0] = 0;
    vector par(A + 1, vector<tuple<int, int, int>>(B + 1, {-1, -1, -1}));
    set<tuple<ll, int, int>> s;
    s.emplace(0, 0, 0);

    auto relax = [&](int a, int b, int i, int na, int nb, ll nd) {
        ll& w = dst[na][nb];
        if (w > nd) {
            s.erase({w, na, nb});
            w = nd;
            par[na][nb] = {a, b, i};
            s.emplace(w, na, nb);
        }
    };

    while (!s.empty()) {
        auto [d, a, b] = *s.begin();
        s.erase(s.begin());

        if (a == x) {
            vector<int> idx;
            for (int i = a, j = b; i != 0 || j != 0; ) {
                auto [i1, j1, id] = par[i][j];
                idx.emplace_back(id);
                i = i1, j = j1;
            }
            reverse(all(idx));
            cout << sz(idx) << ' ' << d << '\n';
            for (int id : idx) cout << moves[id] << '\n';

            return;
        }
        if (a != A) {
            relax(a, b, 0, A, b, d + A - a);
        }

        if (b != B) {
            relax(a, b, 1, a, B, d + B - b);
        }

        if (a != 0) {
            relax(a, b, 2, 0, b, d + a);
        }
        if (b != 0) {
            relax(a, b, 3, a, 0, d + b);
        }
        if (a != 0 && b != B) {
            int t = min(a, B - b);
            relax(a, b, 4, a - t, b + t, d + t);
        }
        if (a != A && b != 0) {
            int t = min(A - a, b);
            relax(a, b, 5, a + t, b - t, d + t);
        }
    }
    cout << -1 << '\n';
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
