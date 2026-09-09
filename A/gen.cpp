#include <bits/stdc++.h>
using namespace std;

// gen: 生成小规模但保证有解的记录。
// 方法: 随机模拟一个含 '-' 的完整合法过程（任意时刻栈中元素互不相同），
// 记录其中的 '+','T','F' 操作作为输入。这样生成的记录必有解。
// 用法: gen [seed]
int main(int argc, char** argv) {
    unsigned long long seed = argc > 1 ? stoull(argv[1]) : 12345;
    mt19937_64 rng(seed);
    int T = 1 + rng() % 4;
    printf("%d\n", T);
    while (T--) {
        int n = 1 + rng() % 9;           // 1..9 条记录操作
        int xr = 2 + rng() % 4;          // 值域大小 2..5，容易碰撞
        bool bigX = (rng() % 4 == 0);    // 偶尔用大数值（接近 1e9）
        vector<int> pool(xr);
        for (int i = 0; i < xr; i++)
            pool[i] = bigX ? (int)(1 + rng() % 1000000000) : i + 1;

        vector<int> st;                  // 栈中存 pool 下标
        vector<char> inSt(xr, 0);
        vector<pair<char,int>> rec;
        while ((int)rec.size() < n) {
            int r = rng() % 100;
            if (r < 15 && !st.empty()) {
                // 隐藏的弹栈（不记录）
                inSt[st.back()] = 0; st.pop_back();
            } else if (r < 55) {
                // 压入：若 x 在栈中，先插入隐藏的弹栈直到 x 被弹掉（制造记录中重复 '+' 的情形）
                int x = rng() % xr;
                while (!st.empty() && inSt[x]) { inSt[st.back()] = 0; st.pop_back(); }
                st.push_back(x); inSt[x] = 1;
                rec.push_back({'+', pool[x]});
            } else {
                // 查询：一半概率对一个栈中元素先插隐藏弹栈再记录 F，否则按当前状态记录
                int x = rng() % xr;
                if (inSt[x] && (rng() & 1)) {
                    while (!st.empty() && inSt[x]) { inSt[st.back()] = 0; st.pop_back(); }
                    rec.push_back({'F', pool[x]});
                } else {
                    rec.push_back({inSt[x] ? 'T' : 'F', pool[x]});
                }
            }
        }
        printf("%d\n", (int)rec.size());
        for (auto& p : rec) printf("%c %d\n", p.first, p.second);
    }
    return 0;
}
