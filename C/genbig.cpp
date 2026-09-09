#include <bits/stdc++.h>
using namespace std;

// usage: genbig <mode> [n] [seed]
// mode 1: single info, identity chain on [1,n]      -> answer 1 2 ... n
// mode 2: single info, reverse chain on [1,n]       -> answer n n-1 ... 1
// mode 3: T = n tests, each "1 1 / 1 1 1"           -> answer n lines of "1"
// mode 4: n positions, n/2 random length-2 infos    -> stress (may be -1)
//         (total info length = n, respecting the sum constraint)
// mode 5: n positions, n/2 duplicate infos "1 2 2 1"-> answer 2 1 3 4 ... n
// mode 6: single test n=1                           -> answer 1
int main(int argc, char** argv) {
    int mode = atoi(argv[1]);
    int n = argc > 2 ? atoi(argv[2]) : 1000000;
    unsigned seed = argc > 3 ? (unsigned)atoi(argv[3]) : 12345;
    mt19937 rng(seed);
    if (mode == 1) {
        printf("1\n%d 1\n1 %d", n, n);
        for (int i = 1; i <= n; i++) printf(" %d", i);
        printf("\n");
    } else if (mode == 2) {
        printf("1\n%d 1\n1 %d", n, n);
        for (int i = n; i >= 1; i--) printf(" %d", i);
        printf("\n");
    } else if (mode == 3) {
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("1 1\n1 1 1\n");
    } else if (mode == 4) {
        printf("1\n%d %d\n", n, n);
        for (int i = 0; i < n; i++) {
            int a = 1 + rng() % n, b = 1 + rng() % n;
            if (a > b) swap(a, b);
            int l = a, r = b;
            printf("%d %d", l, r);
            vector<int> v;
            for (int x = l; x <= r; x++) v.push_back(x);
            shuffle(v.begin(), v.end(), rng);
            for (int x : v) printf(" %d", x);
            printf("\n");
        }
    } else if (mode == 5) {
        printf("1\n%d %d\n", n, n / 2);
        for (int i = 0; i < n / 2; i++) printf("1 2 2 1\n");
    } else if (mode == 6) {
        printf("1\n1 1\n1 1 1\n");
    }
    return 0;
}
