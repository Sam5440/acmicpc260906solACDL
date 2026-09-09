#include <bits/stdc++.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif
using namespace std;

/*
 * 思路：建 trie，cnt[u] = 已插入串中经过节点 u 的串数。
 * f_{i,j} = 所有"cnt >= j"的节点中的最大深度。
 * 插入一个串时，路径上深度 d 的节点计数从 c-1 变 c：
 *   - 对 j < c：该节点在上一轮就已满足 cnt >= j，f_j 不会因此变化；
 *   - 只有 j = c 新获得资格，故只需 g[c] = max(g[c], d)。
 * 于是每个字符只做一次 O(1) 点更新，答案增量维护：
 *   ans += (new ^ c) - (old ^ c)。
 * 总复杂度 O(Σ|s| + n)。
 */

const int MAXNODE = 500000 + 5;
const int MAXN = 500000 + 5;

static int ch[MAXNODE][26];   // trie 儿子，0 = 空（根为节点 0，真实节点编号 >= 1）
static int cnt[MAXNODE];      // 经过每个节点的串数
static int gval[MAXN];        // g[j] = 当前前缀下的 f_{i,j}

namespace IO {
    static char buf[1 << 20];
    static int len = 0, pos = 0;
    inline char getch() {
        if (pos == len) {
            len = (int)fread(buf, 1, sizeof(buf), stdin);
            pos = 0;
            if (len == 0) return 0;
        }
        return buf[pos++];
    }
    inline int readInt() {
        char c = getch();
        while (c && (c < '0' || c > '9')) c = getch();
        int x = 0;
        while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getch(); }
        return x;
    }
    inline int readStr(char* s) {
        char c = getch();
        while (c && (c < 'a' || c > 'z')) c = getch();
        int n = 0;
        while (c >= 'a' && c <= 'z') { s[n++] = c; c = getch(); }
        s[n] = 0;
        return n;
    }
}

static char obuf[1 << 22];
static int opos = 0;
inline void writeLL(long long x) {
    if (x == 0) obuf[opos++] = '0';
    else {
        char tmp[20]; int tn = 0;
        while (x) { tmp[tn++] = char('0' + x % 10); x /= 10; }
        while (tn) obuf[opos++] = tmp[--tn];
    }
    obuf[opos++] = '\n';
    if (opos > (1 << 22) - 64) { fwrite(obuf, 1, opos, stdout); opos = 0; }
}

static char s[MAXNODE];

int main() {
    int n = IO::readInt();
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);   // 本地 Windows 下也输出纯 \n，评测(Linux)无影响
#endif
    int nodes = 1;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int L = IO::readStr(s);
        ans += i;                 // 新位置 j=i，g[i]=0，贡献 (0 ^ i) = i
        int u = 0;
        for (int k = 0; k < L; k++) {
            int c = s[k] - 'a';
            if (!ch[u][c]) ch[u][c] = nodes++;
            u = ch[u][c];
            int nc = ++cnt[u];    // 计数从 nc-1 涨到 nc
            int d = k + 1;        // 节点深度
            if (d > gval[nc]) {
                ans += (long long)((d ^ nc) - (gval[nc] ^ nc));
                gval[nc] = d;
            }
        }
        writeLL(ans);
    }
    fwrite(obuf, 1, opos, stdout);
    return 0;
}
