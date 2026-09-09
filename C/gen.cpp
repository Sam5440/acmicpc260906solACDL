#include <bits/stdc++.h>
using namespace std;

// usage: gen <seed> [maxn=8] [maxm=4]
// Generates small random tests: each info is a random interval [l,r] together
// with a random permutation of [l,r] (exactly the required input format).
int main(int argc, char** argv) {
    int seed = atoi(argv[1]);
    int maxn = argc > 2 ? atoi(argv[2]) : 8;
    int maxm = argc > 3 ? atoi(argv[3]) : 4;
    mt19937 rng(seed);
    int T = 1 + rng() % 3;
    printf("%d\n", T);
    for (int t = 0; t < T; t++) {
        int n = 1 + rng() % maxn;
        int m = 1 + rng() % maxm;
        printf("%d %d\n", n, m);
        for (int i = 0; i < m; i++) {
            int l = 1 + rng() % n;
            int r = l + rng() % (n - l + 1);
            vector<int> v;
            for (int x = l; x <= r; x++) v.push_back(x);
            shuffle(v.begin(), v.end(), rng);
            printf("%d %d", l, r);
            for (int x : v) printf(" %d", x);
            printf("\n");
        }
    }
    return 0;
}
