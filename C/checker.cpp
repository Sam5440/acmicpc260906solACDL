#include <bits/stdc++.h>
using namespace std;

// usage: checker <input> <sol_out> <brute_out>
// Per test: if brute says -1, sol must say -1; otherwise sol must print a
// permutation of 1..n satisfying every chain, with inversions == brute's minimum.
int main(int argc, char** argv) {
    if (argc < 4) { printf("usage: checker input sol_out brute_out\n"); return 2; }
    FILE* fin  = fopen(argv[1], "r");
    FILE* fsol = fopen(argv[2], "r");
    FILE* fans = fopen(argv[3], "r");
    if (!fin || !fsol || !fans) { printf("cannot open files\n"); return 2; }
    int T;
    if (fscanf(fin, "%d", &T) != 1) { printf("bad input\n"); return 2; }
    for (int t = 1; t <= T; t++) {
        int n, m;
        fscanf(fin, "%d %d", &n, &m);
        vector<vector<int>> chains(m);
        for (int i = 0; i < m; i++) {
            int l, r;
            fscanf(fin, "%d %d", &l, &r);
            int k = r - l + 1;
            chains[i].resize(k);
            for (int j = 0; j < k; j++) fscanf(fin, "%d", &chains[i][j]);
        }
        char btok[64];
        if (fscanf(fans, "%63s", btok) != 1) { printf("FAIL test %d: missing brute output\n", t); return 1; }
        bool bunsat = (strcmp(btok, "-1") == 0);
        long long bval = bunsat ? -1 : atoll(btok);

        char tok[64];
        if (fscanf(fsol, "%63s", tok) != 1) { printf("FAIL test %d: missing sol output\n", t); return 1; }
        bool solunsat = (strcmp(tok, "-1") == 0);

        if (bunsat) {
            if (!solunsat) { printf("FAIL test %d: brute=-1 but sol gave a permutation\n", t); return 1; }
            continue;
        }
        if (solunsat) { printf("FAIL test %d: sol=-1 but brute optimum=%lld\n", t, bval); return 1; }

        vector<int> p(n + 1);
        vector<char> seen(n + 1, 0);
        p[1] = atoi(tok);
        for (int i = 2; i <= n; i++)
            if (fscanf(fsol, "%d", &p[i]) != 1) { printf("FAIL test %d: too few numbers\n", t); return 1; }
        for (int i = 1; i <= n; i++) {
            if (p[i] < 1 || p[i] > n || seen[p[i]]) { printf("FAIL test %d: not a permutation of 1..%d\n", t, n); return 1; }
            seen[p[i]] = 1;
        }
        for (auto &c : chains)
            for (int j = 0; j + 1 < (int)c.size(); j++)
                if (p[c[j]] > p[c[j + 1]]) {
                    printf("FAIL test %d: constraint violated (p[%d]=%d > p[%d]=%d)\n",
                           t, c[j], p[c[j]], c[j + 1], p[c[j + 1]]);
                    return 1;
                }
        long long inv = 0;
        for (int a = 1; a <= n; a++)
            for (int b = a + 1; b <= n; b++)
                if (p[a] > p[b]) inv++;
        if (inv != bval) {
            printf("FAIL test %d: sol inversions=%lld, brute optimum=%lld\n", t, inv, bval);
            return 1;
        }
    }
    printf("All %d tests OK\n", T);
    return 0;
}
