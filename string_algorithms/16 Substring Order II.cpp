#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
using namespace std;

using ll = int64_t;
const int M = 1e5 + 10, LOG = 18;
int lcp[M];
ll pref[M];
vector<int> sa, pos;
void suffix_array(string & s) {
    int n = sz(s);
    vector<int> c(n), cur(n);
    sa.resize(n), pos.resize(n);
    for (int i = 0; i < n; ++i) {
        sa[i] = i, c[i] = s[i];
    }
    sort(sa.begin(), sa.end(), [&](int i, int j) { return c[i] < c[j]; });
    int cnt[M];
    for (int k = 1; k < n; k <<= 1) {
        fill(cnt, cnt + M, 0);
        for (int x : c) cnt[x]++;
        for (int i = 1; i < M; ++i) cnt[i] += cnt[i - 1];
        for (int i : sa) {
            int c2 = c[(i - k + n) % n] - 1;
            cur[cnt[c2]++] = (i - k + n) % n;
        }
        swap(cur, sa);
        int x = -1, y = -1, p = 0;
        for (int i : sa) {
            if (x != c[i] || y != c[(i + k) % n]) {
                x = c[i], y = c[(i + k) % n], p++;
            }
            cur[i] = p;
        }
        swap(cur, c);
    }
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    int l = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            l = 0;
        } else {
            while (s[(i + l) % n] == s[(sa[pos[i] + 1] + l) % n]) l++;
            lcp[pos[i]] = l;
            l = max(0, l - 1);
        }
    }
}
ll rmq[LOG][M];
void build_rmq() {
    for (int i = 0; i < M; ++i) {
        rmq[0][i] = lcp[i];
    }
    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i + (1 << k) <= M; ++i) {
            ll l1 = rmq[k - 1][i], l2 = rmq[k - 1][i + (1 << (k - 1))];
            rmq[k][i] = min(l1, l2);
        }
    }
}
int get_right_less(int p, int k) {
    for (int i = LOG - 1; i >= 0; --i) {
        if (rmq[i][p] >= k) p += (1 << i);
    }
    return p + 1;
}
const ll P = 533, MOD = 998244353;
ll pw[M], h[M];
vector<ll> h2{0};
inline ll get_h(int l, int r) {
    return (h[r] - h[l] * pw[r - l] % MOD + MOD) % MOD;
}
inline ll get_pref(int l, int r) {
    return pref[r] - pref[l];
}
int n;
string str, cur;
inline bool mless(int i) {
    int lo = 0, hi = min(n - i + 1, sz(h2));
    while (hi - lo > 1) {
        int md = (hi - lo) / 2 + lo;
        if (h2[md] == get_h(i, i + md)) {
            lo = md;
        } else {
            hi = md;
        }
    }
    if (lo == sz(h2) - 1) return true;
    if (lo == n - i) return false;
    return cur[lo] < str[i + lo];
}

inline int lower_bound() {
    int lo = 0, hi = n + 1;
    while (hi - lo > 1) {
        int md = (hi - lo) / 2 + lo;
        if (mless(sa[md])) {
            hi = md;
        } else {
            lo = md;
        }
    }
    return hi;
}


void solve() {
    ll k;
    cin >> str >> k;
    n = sz(str);
    pw[0] = 1;
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = pw[i] * P % MOD;
        h[i + 1] = (h[i] * P + str[i] - 'a' + 1) % MOD;
    }
    str += '#';
    suffix_array(str);
    build_rmq();
    for (int i = 0; i <= n; ++i) pref[i + 1] = pref[i] + n - sa[i];
    int l, r;
    for (int i = 0; ; ++i) {
        cur += 'a';
        h2.emplace_back((h2.back() * P + 1) % MOD);
        l = lower_bound();
        for (char x = 'a'; x <= 'z'; ++x) {
            if (sa[l] + i >= n || str[sa[l] + i] != x) {
                cur.back()++;
                h2.back()++;
                continue;
            }
            r = get_right_less(l, i + 1);
            if (r - l >=  k) {
                cout << cur << '\n';
                return;
            }
            ll sm = get_pref(l, r) - ll(r - l) * i;
            if (k > sm) {
                k -= sm;
                cur.back()++;
                h2.back()++;
                l = r;
                continue;
            }
            k -= (r - l);
            break;
        }
    }
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