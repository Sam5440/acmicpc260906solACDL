#include <bits/stdc++.h>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif
using namespace std;

struct FastScanner {
    static constexpr int SZ = 1 << 20;
    char buf[SZ];
    int p = 0, len = 0;

    char getChar() {
        if (p == len) {
            len = (int)fread(buf, 1, SZ, stdin);
            p = 0;
            if (!len) return 0;
        }
        return buf[p++];
    }

    int readInt() {
        char c = getChar();
        while (c && (c < '0' || c > '9')) c = getChar();
        int x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getChar();
        }
        return x;
    }

    char readOp() {
        char c = getChar();
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getChar();
        return c;
    }
};

int main() {
#ifdef _WIN32
    // Windows 重定向默认可能把换行写成 CRLF；样例逐字节比对需要保持 LF。
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    FastScanner fs;
    int T = fs.readInt();

    string answer;
    answer.reserve(2'200'000);

    vector<int> op, x, id, values, nxt, lastT, deadline, needAliveUntil;
    vector<char> inStack;

    struct Node {
        int id;              // 离散化后的元素值
        int needAliveUntil;  // 该份元素最后一次必须还在栈中的位置
        int forcedPopBy;     // 若保持当前上下关系，栈顶最晚必须弹出的边界
    };
    vector<Node> st;

    auto popTop = [&]() {
        inStack[st.back().id] = 0;
        st.pop_back();
        answer.push_back('-');
    };

    while (T--) {
        int n = fs.readInt();
        op.resize(n);
        x.resize(n);
        id.resize(n);

        for (int i = 0; i < n; ++i) {
            char c = fs.readOp();
            x[i] = fs.readInt();
            if (c == '+') op[i] = 0;
            else if (c == 'T') op[i] = 1;
            else op[i] = 2; // F
        }

        values = x;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        int m = (int)values.size();
        for (int i = 0; i < n; ++i) {
            id[i] = (int)(lower_bound(values.begin(), values.end(), x[i]) - values.begin());
        }

        // 对每个压入操作预处理两个量：
        // deadline：下一次同值压入或 false 查询的位置，当前这份值必须在那之前离开。
        // needAliveUntil：在 deadline 前最后一次 true 查询的位置；若没有，只需活到本次压入。
        deadline.assign(n, n + 1);
        needAliveUntil.assign(n, 0);
        nxt.assign(m, n + 1);
        lastT.assign(m, 0);
        for (int i = n - 1; i >= 0; --i) {
            int v = id[i];
            if (op[i] == 1) {
                if (!lastT[v]) lastT[v] = i + 1;
            } else {
                if (op[i] == 0) {
                    deadline[i] = nxt[v];
                    needAliveUntil[i] = lastT[v] ? lastT[v] : i + 1;
                }
                nxt[v] = i + 1;
                lastT[v] = 0;
            }
        }

        inStack.assign(m, 0);
        st.clear();

        for (int i = 0; i < n; ++i) {
            int pos = i + 1;

            // 栈顶如果已经过了最后一次必须为 true 的查询，就可以安全弹掉。
            while (!st.empty() && st.back().needAliveUntil < pos) popTop();

            int v = id[i];
            if (op[i] == 0) { // 压入 x
                // 若旧的 x 还在栈中，为保证元素互异，它以及其上的元素必须先弹出。
                if (inStack[v]) {
                    while (true) {
                        int topId = st.back().id;
                        popTop();
                        if (topId == v) break;
                    }
                }

                // 新元素需要一直活到 needAliveUntil[i]。若当前栈顶为了满足自己或更下面元素的
                // deadline，最晚必须在此之前弹出，就不能让新元素压在它上面，先把它弹掉。
                while (!st.empty() && st.back().forcedPopBy <= needAliveUntil[i]) popTop();

                int forcedPopBy = deadline[i];
                if (!st.empty()) forcedPopBy = min(forcedPopBy, st.back().forcedPopBy);

                st.push_back({v, needAliveUntil[i], forcedPopBy});
                inStack[v] = 1;
                answer.push_back('+');
            } else if (op[i] == 2) { // F x
                // 查询为 false 时，如果 x 还在栈里，必须弹到 x 离开为止。
                if (inStack[v]) {
                    while (true) {
                        int topId = st.back().id;
                        popTop();
                        if (topId == v) break;
                    }
                }
                answer.push_back('?');
            } else { // T x
                answer.push_back('?');
            }
        }

        // 题目允许在记录末尾继续插入弹栈；清空栈可得到稳定、样例一致的输出形式。
        while (!st.empty()) popTop();
        answer.push_back('\n');
    }

    fwrite(answer.data(), 1, answer.size(), stdout);
    return 0;
}
