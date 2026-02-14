#include <bits/stdc++.h>

#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& el : a) cin >> el;

    vector<int> lb(n, -1), rb(n, n), st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] < a[i]) {
            rb[st.back()] = i;
            st.pop_back();
        }
        lb[i] = st.empty() ? -1 :
                a[st.back()] == a[i] ? lb[st.back()] :
                st.back();
        st.emplace_back(i);
    }

    vector<int> dp(n);
    vector<int> idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&a](int i, int j) {
        return a[i] > a[j];
    });
    for (int i : idx) {
        int left = lb[i] == -1 ? 0 : dp[lb[i]];
        int right = rb[i] == n ? 0 : dp[rb[i]];
        dp[i] = 1 + max(left, right);
    }
    cout << *max_element(all(dp)) << '\n';
}