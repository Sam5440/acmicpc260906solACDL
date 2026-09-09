#include <bits/stdc++.h>
using namespace std;

// Brute force: enumerate all permutations (n <= 8), keep the minimum inversion
// count among those satisfying every chain. Output per test: "-1" or the count.
int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        vector<vector<int>> chains(m);
        for (int i = 0; i < m; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            int k = r - l + 1;
            chains[i].resize(k);
            for (int j = 0; j < k; j++) scanf("%d", &chains[i][j]);
        }
        vector<int> p(n);
        iota(p.begin(), p.end(), 1);
        long long best = -1;
        do {
            bool ok = true;
            for (auto &c : chains) {
                for (int j = 0; j + 1 < (int)c.size(); j++)
                    if (p[c[j] - 1] > p[c[j + 1] - 1]) { ok = false; break; }
                if (!ok) break;
            }
            if (!ok) continue;
            long long inv = 0;
            for (int a = 0; a < n; a++)
                for (int b = a + 1; b < n; b++)
                    if (p[a] > p[b]) inv++;
            if (best == -1 || inv < best) best = inv;
        } while (next_permutation(p.begin(), p.end()));
        if (best == -1) printf("-1\n");
        else printf("%lld\n", best);
    }
    return 0;
}
