#include <bits/stdc++.h>
using namespace std;

// 正确贪心：
// 对每个压入 p（值为 x）：d(p) = 之后第一个 '+x'/'Fx' 的位置（p 必须在此之前弹出，无则为 n+1），
// r(p) = (p, d(p)) 内最后一个 'Tx' 的位置（p 必须活到那之后，无则为 p 自身位置）。
// LIFO 推出：p 的实际弹出时刻 <= g(p) := min(d(p), g(p 下面的元素)）。
// 模拟时：
//   '+ x'：若 x 在栈中，先弹到 x 为止；再弹出所有 g(top) <= r(新元素) 的栈顶
//          （否则新元素压在它上面必然活不到自己的 r）；然后压入。
//   'F x'：若 x 在栈中，弹到 x 为止。
//   'T x'：直接记录（可证明有解时 x 必在栈中）。
// d、r 倒扫一遍对每个值维护 "下一个 +/F 位置" 和 "区间内最右 T 位置" 预处理。

int main() {
    static char buf[1 << 26];
    size_t len = fread(buf, 1, sizeof(buf), stdin), pos = 0;
    auto readInt = [&]() -> long long {
        while (pos < len && (buf[pos] < '0' || buf[pos] > '9')) pos++;
        long long x = 0;
        while (pos < len && buf[pos] >= '0' && buf[pos] <= '9') x = x * 10 + (buf[pos++] - '0');
        return x;
    };
    auto readTok = [&]() -> char {
        while (pos < len && (buf[pos] == ' ' || buf[pos] == '\n' || buf[pos] == '\r' || buf[pos] == '\t')) pos++;
        return buf[pos++];
    };

    int T = (int)readInt();
    string out;
    out.reserve(1 << 22);
    vector<int> op, xs, val, comp, d, r, nxt, lastT; // op: 0='+' 1='T' 2='F'
    vector<char> inSt;
    struct Node { int v, d, g; };
    vector<Node> st;
    while (T--) {
        int n = (int)readInt();
        op.resize(n); xs.resize(n); val.resize(n);
        for (int i = 0; i < n; i++) {
            char c = readTok();
            xs[i] = (int)readInt();
            op[i] = c == '+' ? 0 : c == 'T' ? 1 : 2;
        }
        // 离散化
        comp = xs;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        int m = (int)comp.size();
        for (int i = 0; i < n; i++)
            val[i] = (int)(lower_bound(comp.begin(), comp.end(), xs[i]) - comp.begin());
        // 倒扫求 d、r（位置用 1-based，n+1 表示"没有下一个 +/F"）
        d.assign(n, 0); r.assign(n, 0);
        nxt.assign(m, n + 1); lastT.assign(m, 0);
        for (int i = n - 1; i >= 0; i--) {
            int v = val[i];
            if (op[i] == 1) {
                if (!lastT[v]) lastT[v] = i + 1;
            } else {
                if (op[i] == 0) {
                    d[i] = nxt[v];
                    r[i] = lastT[v] ? lastT[v] : i + 1;
                }
                nxt[v] = i + 1;
                lastT[v] = 0;
            }
        }
        // 正扫模拟
        inSt.assign(m, 0);
        st.clear();
        for (int i = 0; i < n; i++) {
            int v = val[i];
            if (op[i] == 0) {
                if (inSt[v]) { // 弹到 x 为止
                    while (true) {
                        Node nd = st.back(); st.pop_back();
                        inSt[nd.v] = 0; out.push_back('-');
                        if (nd.v == v) break;
                    }
                }
                // 弹出所有 g(top) <= r(新元素) 的栈顶
                int rr = r[i];
                while (!st.empty() && st.back().g <= rr) {
                    inSt[st.back().v] = 0; st.pop_back();
                    out.push_back('-');
                }
                int g = d[i];
                if (!st.empty() && st.back().g < g) g = st.back().g;
                st.push_back({v, d[i], g});
                inSt[v] = 1;
                out.push_back('+');
            } else if (op[i] == 2) {
                if (inSt[v]) { // 弹到 x 为止
                    while (true) {
                        Node nd = st.back(); st.pop_back();
                        inSt[nd.v] = 0; out.push_back('-');
                        if (nd.v == v) break;
                    }
                }
                out.push_back('?');
            } else {
                out.push_back('?');
            }
        }
        out.push_back('\n');
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
