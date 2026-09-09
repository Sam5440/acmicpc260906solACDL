#include <bits/stdc++.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif
using namespace std;

// 暴力：对每个 i 枚举全部子集，按大小 j 取 LCP 最大值。
// 仅用于小数据对拍（n <= ~12）。

int main() {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    int n;
    if (scanf("%d", &n) != 1) return 0;
    vector<string> s(n + 1);
    static char buf[1024];
    for (int i = 1; i <= n; i++) { scanf("%s", buf); s[i] = buf; }
    for (int i = 1; i <= n; i++) {
        vector<int> f(i + 1, 0);
        for (int mask = 1; mask < (1 << i); mask++) {
            int j = __builtin_popcount(mask);
            int lcp = INT_MAX, first = -1;
            for (int k = 0; k < i; k++) if ((mask >> k) & 1) {
                if (first == -1) { first = k; lcp = (int)s[k + 1].size(); }
                else {
                    int x = 0;
                    while (x < (int)s[first + 1].size() && x < (int)s[k + 1].size()
                           && s[first + 1][x] == s[k + 1][x]) x++;
                    lcp = min(lcp, x);
                }
            }
            f[j] = max(f[j], lcp);
        }
        long long ans = 0;
        for (int j = 1; j <= i; j++) ans += (long long)(f[j] ^ j);
        printf("%lld\n", ans);
    }
    return 0;
}
