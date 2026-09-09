#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<int> cnt(n + 1, 0);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++cnt[x];
            sum += x;
        }

        int small = 0;
        while (small <= n && 1LL * small * (n - small) != sum) ++small;

        long long ans = 1;
        int big = 0;

        for (int i = 0; i < small; ++i) {
            if (big == i) ans = ans * 2 % MOD;

            big += cnt[i];
            cnt[i] = 0;

            --cnt[big];
        }

        if (big == small && cnt[small] > 0) {
            ans = ans * 2 % MOD;
        }

        cout << ans % MOD << '\n';
    }
    return 0;
}
