#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define dbg(x) {cerr << #x << ": " << x << '\n';}
using namespace std;
using ll = int64_t;
const int N = 500;
int arr[N][N];
int full_row[N], full_col[N];
const ll MOD = 1e9 + 7;
map<array<ll, 4>, ll> dp, dp2;

void solve() {
    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        for (int j = 0; j < n; ++j) {
            arr[i][j] = s[j] == '.' ? -1 : s[j] - 'A';
        }
    }
    int cnt0ab = 0, cnt0a = 0, cnt0b = 0, cnt0 = 0;
    int cnt1ab = 0, cnt1a = 0, cnt1b = 0, cnt1 = 0;
    for (int i = 0; i < n; ++i) {
        bool a = false, b = false;
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == 0) a = true;
            if (arr[i][j] == 1) b = true;
        }
        full_row[i] = a && b;
        if (a && b) ++cnt0ab;
        if (a && !b) ++cnt0a;
        if (!a && b) ++cnt0b;
        if (!a && !b) ++cnt0;
    }
    for (int i = 0; i < n; ++i) {
        bool a = false, b = false;
        for (int j = 0; j < n; ++j) {
            if (arr[j][i] == 0) a = true;
            if (arr[j][i] == 1) b = true;
        }
        full_col[i] = a && b;
        if (a && b) ++cnt1ab;
        if (a && !b) ++cnt1a;
        if (!a && b) ++cnt1b;
        if (!a && !b) ++cnt1;
    }
    int ca = 0, cb = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] == 0 && !full_row[i] && !full_col[j]) ++ca;
            if (arr[i][j] == 1 && !full_row[i] && !full_col[j]) ++cb;
        }
    }

    dp[{cnt0a, cnt0b, cnt0, ca}] = 1;
    for (int i = 0; i < cnt1a; ++i) {
        for (auto& [c, val] : dp) {
            if (c[3] != 0) {
                if (c[0] > 0 && c[3] > 1) (dp2[{c[0] - 1, c[1], c[2], c[3] - 2}] += val * (c[3] - 1)) %= MOD;
                if (c[0] > 0) (dp2[{c[0] - 1, c[1], c[2], c[3] - 1}] += val * (c[0] - c[3])) %= MOD;
                if (c[2] > 0) (dp2[{c[0], c[1] + 1, c[2] - 1, c[3] - 1}] += val * c[2]) %= MOD;
            } else {
                if (c[0] > 0) (dp2[{c[0] - 1, c[1], c[2], 0}] += val * c[0]) %= MOD;
                if (c[2] > 0) (dp2[{c[0], c[1] + 1, c[2] - 1, 0}] += val * c[2]) %= MOD;
            }
        }
        swap(dp, dp2);
        dp2.clear();
    }

    for (auto& [c, val] : dp) {
        dp2[{c[0], c[1], c[2], cb}] = val;
    }
    swap(dp, dp2);
    dp2.clear();
    for (int i = 0; i < cnt1b; ++i) {
        for (auto& [c, val] : dp) {
            if (c[3] != 0) {
                if (c[1] > 0 && c[3] > 1) (dp2[{c[0], c[1] - 1, c[2], c[3] - 2}] += val * (c[3] - 1)) %= MOD;
                if (c[1] > 0) (dp2[{c[0], c[1] - 1, c[2], c[3] - 1}] += val * (c[1] - c[3])) %= MOD;
                if (c[2] > 0) (dp2[{c[0] + 1, c[1], c[2] - 1, c[3] - 1}] += val * c[2]) %= MOD;
            } else {
                if (c[1] > 0) (dp2[{c[0], c[1] - 1, c[2], 0}] += val * c[1]) %= MOD;
                if (c[2] > 0) (dp2[{c[0] + 1, c[1], c[2] - 1, 0}] += val * c[2]) %= MOD;
            }
        }
        swap(dp, dp2);
        dp2.clear();
    }

    for (int i = 0; i < cnt1; ++i) {
        for (auto& [c, val] : dp) {
            if (c[0] > 0 && c[1] > 0) (dp2[{c[0] - 1, c[1] - 1, c[2]}] += val * c[0] * c[1]) %= MOD;
            if (c[2] > 0) (dp2[{c[0], c[1], c[2] - 1}] += val * c[2] * (c[0] + c[1])) %= MOD;
            if (c[2] > 1) (dp2[{c[0] + 1, c[1] + 1, c[2] - 2}] += val * c[2] * (c[2] - 1)) %= MOD;
        }
        swap(dp, dp2);
        dp2.clear();
    }
    cout << dp[{0, 0, 0, 0}] << '\n';

}

signed main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
#else
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
#endif
    solve();
    return 0;
}