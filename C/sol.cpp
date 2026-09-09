#include <bits/stdc++.h>
using namespace std;

// ---------- fast input ----------
static const int BUFSIZE = 1 << 20;
static char ibuf[BUFSIZE];
static int ipos = 0, ilen = 0;
static inline int readChar() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, BUFSIZE, stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return (unsigned char)ibuf[ipos++];
}
static inline int readInt() {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

// ---------- reusable storage (sum n, sum edges <= 1e6 over the whole file) ----------
const int MAXV = 1000000 + 5;
int head[MAXV];   // adjacency head per position
int indeg[MAXV];  // indegree per position
int ans[MAXV];    // ans[pos] = value assigned to position
int to[MAXV], nxt[MAXV];

int main() {
    int T = readInt();
    string out;
    out.reserve(1 << 22);
    char tmp[16];
    while (T--) {
        int n = readInt(), m = readInt();
        for (int i = 1; i <= n; i++) { head[i] = -1; indeg[i] = 0; }
        int ec = 0;
        for (int i = 0; i < m; i++) {
            int l = readInt(), r = readInt();
            int k = r - l + 1;
            int prev = readInt();          // q_1
            for (int j = 1; j < k; j++) {
                int cur = readInt();       // q_{j+1}; constraint p[prev] < p[cur]
                to[ec] = cur; nxt[ec] = head[prev]; head[prev] = ec; ec++;
                indeg[cur]++;
                prev = cur;
            }
        }
        // Kahn, always taking the available position with the smallest index
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= n; i++) if (indeg[i] == 0) pq.push(i);
        int cnt = 0;
        while (!pq.empty()) {
            int x = pq.top(); pq.pop();
            ans[x] = ++cnt;
            for (int e = head[x]; e != -1; e = nxt[e]) {
                int y = to[e];
                if (--indeg[y] == 0) pq.push(y);
            }
        }
        if (cnt < n) {
            out += "-1\n";
        } else {
            for (int i = 1; i <= n; i++) {
                int w = sprintf(tmp, "%d", ans[i]);
                out.append(tmp, w);
                out += (i == n ? '\n' : ' ');
            }
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
