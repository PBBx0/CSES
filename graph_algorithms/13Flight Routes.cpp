#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) cerr << #x << " = " << x << '\n';
using namespace std;

using ll = int64_t;
const int N = 1e5, K = 10;
const ll INF = 1e15;
vector<pair<int, ll>> g[N];
ll d[N][K];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> s;
int cnt[N];
void solve() {
    for (auto& a : d) for (auto& el : a) el = INF;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].emplace_back(b, c);
    }
    d[0][0] = 0;

    for (int v = 0; v < n; ++v) {
        for (int i = 0; i < k; ++i) {
            s.emplace(d[v][i], v + i * n);
        }
    }
    auto get_ma = [&](int v) {
        int id = 0;
        for (int i = 0; i < k; ++i) {
            if (d[v][i] > d[v][id]) {
                id = i;
            }
        }
        return id;
    };
//    int cnt1 = 0, cnt2 = 0;

    while (!s.empty()) {
//        cnt1++;
        auto [dist, v] = s.top();
        s.pop();
        v %= n;
        if (cnt[v] == k) continue;
        cnt[v]++;
        for (auto [to, w] : g[v]) {
//            cnt2++;
            int i = get_ma(to);
            ll& x = d[to][i];
            if (x > dist + w) {
                int nv = to + i * n;
                x = dist + w;
                s.emplace(x, nv);
            }
        }
    }
//    dbg(cnt1)
//    dbg(cnt2)

    sort(d[n - 1], d[n - 1] + k);
    for (int i = 0; i < k; ++i) cout << d[n - 1][i] << ' ';
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    auto start = clock();
    solve();
    cerr << (clock() - start) * 1000 / CLOCKS_PER_SEC << '\n';
    return 0;
}