// 基于“游程事件过程”模型的递归计数：
// 把串看作从 (0,0) 出发、交替向右(H)/向上(V) 的阶梯路径。
// H 回合取值 = 当前 V 总和 SB（被迫），选择拿 k 份（k = 该游程长度）；
// V 回合取值 = 当前 H 总和 SA。拿完所有池子即成功。
// 计数乘 2（首位比特两种）。
#include <bits/stdc++.h>
using namespace std;
int n;
map<int,int> pool;
long long ans;
void dfs(int SA, int SB, int turn){ // turn 0=H, 1=V
  if(pool.empty()){ ans++; return; }
  int v = (turn==0 ? SB : SA);
  auto it = pool.find(v);
  if(it==pool.end()) return;
  int R = it->second;
  int own = (turn==0 ? SA : SB);
  for(int k=1;k<=R;k++){
    if(k<R && own+k>v) continue; // 留下剩余但对方总和已超过 v，剩余永远无法被取 -> 死路
    it->second -= k;
    if(it->second==0) pool.erase(it);
    if(turn==0) dfs(SA+k, SB, 1); else dfs(SA, SB+k, 0);
    pool[v]+=k;
    it = pool.find(v);
  }
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){int x;scanf("%d",&x);pool[x]++;}
  ans=0;
  dfs(0,0,0);
  printf("%lld\n", ans*2);
}
