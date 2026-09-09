#include <bits/stdc++.h>
using namespace std;

// 用法: gen seed [mode]
// mode 缺省 = seed % 7（小数据对拍）; 100..105 为大数据/边界数据。

mt19937 rng;

string randStr(int len, int alpha) {
    string s;
    for (int i = 0; i < len; i++) s += char('a' + rng() % alpha);
    return s;
}

int main(int argc, char** argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 1;
    int mode = argc > 2 ? atoi(argv[2]) : (seed % 7);
    rng.seed(seed * 1000003u + 7);

    if (mode == 0) {                 // 纯随机，字符集 {a,b}
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("%s\n", randStr(1 + rng() % 8, 2).c_str());
    } else if (mode == 1) {          // 纯随机，字符集 a-z（几乎无公共前缀）
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("%s\n", randStr(1 + rng() % 8, 26).c_str());
    } else if (mode == 2) {          // 全相同
        int n = 1 + rng() % 10;
        string s = randStr(1 + rng() % 6, 2);
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("%s\n", s.c_str());
    } else if (mode == 3) {          // 链式：s_i 是 s_{i-1} 加一个字符
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        string s = randStr(1, 2);
        for (int i = 0; i < n; i++) {
            printf("%s\n", s.c_str());
            s += char('a' + rng() % 2);
        }
    } else if (mode == 4) {          // 少量基串 + 随机加长（制造分叉的公共前缀）
        int nb = 1 + rng() % 3;
        vector<string> bases(nb);
        for (auto& b : bases) b = randStr(1 + rng() % 4, 2);
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            string s = bases[rng() % nb];
            if (rng() % 2) s += randStr(1 + rng() % 2, 2);
            printf("%s\n", s.c_str());
        }
    } else if (mode == 5) {          // 全是单字符
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) printf("%c\n", 'a' + (int)(rng() % 2));
    } else if (mode == 6) {          // 混合：有时重复上一个串
        int n = 1 + rng() % 10;
        printf("%d\n", n);
        string prev;
        for (int i = 0; i < n; i++) {
            string s;
            if (!prev.empty() && rng() % 3 == 0) s = prev;
            else s = randStr(1 + rng() % 5, 3);
            printf("%s\n", s.c_str());
            prev = s;
        }
    } else if (mode == 100) {        // n=5e5 全 "a"，深度只有 1，计数很大
        printf("500000\n");
        for (int i = 0; i < 500000; i++) printf("a\n");
    } else if (mode == 101) {        // n=1，单串长 5e5
        printf("1\n%s\n", randStr(500000, 26).c_str());
    } else if (mode == 102) {        // 链 a, aa, ..., a^999（总长 499500）
        printf("999\n");
        string s;
        for (int i = 0; i < 999; i++) { s += 'a'; printf("%s\n", s.c_str()); }
    } else if (mode == 103) {        // 25 万个 "ab"（总长 5e5，深度 2 计数 25 万）
        printf("250000\n");
        for (int i = 0; i < 250000; i++) printf("ab\n");
    } else if (mode == 104) {        // 大随机，字符集 {a,b}，总长 <= 5e5
        vector<string> v; int sum = 0;
        while (true) {
            int l = 1 + rng() % 12;
            if (sum + l > 500000) break;
            v.push_back(randStr(l, 2)); sum += l;
        }
        printf("%d\n", (int)v.size());
        for (auto& s : v) printf("%s\n", s.c_str());
    } else if (mode == 105) {        // 1000 个串共享 300 长公共前缀 + 200 随机尾
        string base = randStr(300, 2);
        printf("1000\n");
        for (int i = 0; i < 1000; i++) printf("%s\n", (base + randStr(200, 2)).c_str());
    }
    return 0;
}
