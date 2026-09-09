#include <bits/stdc++.h>
using namespace std;

// checker: 校验 output 是否为 input 记录的合法重构。
// 用法: checker <input_file> <output_file>
// 校验: (a) 删去 '-' 后与记录一致; (b) 任意时刻栈中元素互不相同;
//       (c) 弹栈时栈非空; (d) 每个查询结果与记录相符; (e) 记录恰好被消费完, 输出恰好 T 行。
int main(int argc, char** argv) {
    if (argc < 3) { fprintf(stderr, "usage: checker input output\n"); return 2; }
    FILE* fi = fopen(argv[1], "rb");
    FILE* fo = fopen(argv[2], "rb");
    if (!fi || !fo) { fprintf(stderr, "checker: cannot open files\n"); return 2; }

    string outAll;
    {
        char b[65536]; size_t r;
        while ((r = fread(b, 1, sizeof(b), fo)) > 0) outAll.append(b, r);
    }
    vector<string> toks;
    {
        string cur;
        for (char c : outAll) {
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
                if (!cur.empty()) { toks.push_back(cur); cur.clear(); }
            } else cur.push_back(c);
        }
        if (!cur.empty()) toks.push_back(cur);
    }

    int T;
    if (fscanf(fi, "%d", &T) != 1) { fprintf(stderr, "checker: bad input\n"); return 2; }
    size_t ti = 0;
    for (int tc = 1; tc <= T; tc++) {
        int n; fscanf(fi, "%d", &n);
        vector<int> typ(n), x(n);
        char tb[8];
        for (int i = 0; i < n; i++) {
            fscanf(fi, "%7s %d", tb, &x[i]);
            typ[i] = tb[0] == '+' ? 0 : tb[0] == 'T' ? 1 : 2;
        }
        if (ti >= toks.size()) { fprintf(stderr, "FAIL test %d: missing output line\n", tc); return 1; }
        const string& s = toks[ti++];
        vector<int> st;
        unordered_set<int> in;
        int idx = 0;
        bool bad = false;
        string msg;
        for (size_t p = 0; p < s.size() && !bad; p++) {
            char c = s[p];
            if (c == '-') {
                if (st.empty()) { bad = true; msg = "pop from empty stack"; }
                else { in.erase(st.back()); st.pop_back(); }
            } else if (c == '+') {
                if (idx >= n || typ[idx] != 0) { bad = true; msg = "'+' does not match record"; }
                else {
                    int v = x[idx++];
                    if (in.count(v)) { bad = true; msg = "duplicate element in stack"; }
                    else { st.push_back(v); in.insert(v); }
                }
            } else if (c == '?') {
                if (idx >= n || typ[idx] == 0) { bad = true; msg = "'?' does not match record"; }
                else {
                    int v = x[idx];
                    bool pres = in.count(v);
                    bool expect = (typ[idx] == 1);
                    idx++;
                    if (pres != expect) { bad = true; msg = "query answer mismatch"; }
                }
            } else { bad = true; msg = "invalid character in output"; }
        }
        if (!bad && idx != n) { bad = true; msg = "record not fully consumed"; }
        if (bad) {
            fprintf(stderr, "FAIL test %d: %s\n", tc, msg.c_str());
            return 1;
        }
    }
    if (ti != toks.size()) { fprintf(stderr, "FAIL: extra output tokens\n"); return 1; }
    printf("OK\n");
    return 0;
}
