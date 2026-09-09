#include <bits/stdc++.h>
using namespace std;

// 暴力：在每条记录操作之前枚举插入 0..栈大小 个 '-'，DFS + 记忆化找任意合法序列。
// 仅用于小规模（n <= 10 左右）。
int n;
vector<int> typ; // 0='+' 1='T' 2='F'
vector<int> val;
vector<int> st;
string ans;
set<string> bad;

static string keyOf(int i, const vector<int>& s) {
    string k = to_string(i) + "|";
    for (int v : s) { k += to_string(v); k += ','; }
    return k;
}

bool dfs(int i, string& cur) {
    if (i == n) { ans = cur; return true; }
    string key = keyOf(i, st);
    if (bad.count(key)) return false;
    int x = val[i];
    for (int k = 0; k <= (int)st.size(); k++) {
        vector<int> popped;
        for (int j = 0; j < k; j++) { popped.push_back(st.back()); st.pop_back(); cur.push_back('-'); }
        bool present = find(st.begin(), st.end(), x) != st.end();
        bool ok = false;
        if (typ[i] == 0 && !present) {
            st.push_back(x); cur.push_back('+');
            ok = dfs(i + 1, cur);
            cur.pop_back(); st.pop_back();
        } else if (typ[i] == 1 && present) {
            cur.push_back('?');
            ok = dfs(i + 1, cur);
            cur.pop_back();
        } else if (typ[i] == 2 && !present) {
            cur.push_back('?');
            ok = dfs(i + 1, cur);
            cur.pop_back();
        }
        for (int j = k - 1; j >= 0; j--) st.push_back(popped[j]);
        cur.resize(cur.size() - k);
        if (ok) return true;
    }
    bad.insert(key);
    return false;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 1;
    string outAll;
    while (T--) {
        scanf("%d", &n);
        typ.resize(n); val.resize(n);
        char tb[8];
        for (int i = 0; i < n; i++) {
            scanf("%7s %d", tb, &val[i]);
            typ[i] = tb[0] == '+' ? 0 : tb[0] == 'T' ? 1 : 2;
        }
        st.clear(); bad.clear(); ans.clear();
        string cur;
        if (!dfs(0, cur)) {
            fprintf(stderr, "brute: no valid sequence found (data unsolvable?)\n");
            return 1;
        }
        outAll += ans;
        outAll += '\n';
    }
    fputs(outAll.c_str(), stdout);
    return 0;
}
