// 校验性质：每个节点的成功 k 集合 ⊆ {R, v-own}；且二元时两子树计数相等
#include <bits/stdc++.h>
using namespace std;
int n;
map<int,int> pool;
bool bad=false;
long long dfs(int SA, int SB, int turn){
  if(pool.empty()) return 1;
  int v = (turn==0 ? SB : SA);
  auto it = pool.find(v);
  if(it==pool.end()) return 0;
  int R = it->second;
  int own = (turn==0 ? SA : SB);
  vector<pair<int,long long>> good;
  for(int k=1;k<=R;k++){
    if(k<R && own+k>v) continue;
    it->second -= k;
    if(it->second==0) pool.erase(it);
    long long sub = (turn==0 ? dfs(SA+k, SB, 1) : dfs(SA, SB+k, 0));
    pool[v]+=k;
    it = pool.find(v);
    if(sub>0) good.push_back({k,sub});
  }
  // 检查
  for(auto&g:good){
    if(g.first!=R && g.first!=v-own){
      printf("BADK SA=%d SB=%d turn=%d v=%d R=%d k=%d c=%lld\n",SA,SB,turn,v,R,g.first,g.second);
      bad=true;
    }
  }
  if(good.size()>2){ printf("SIZE>2\n"); bad=true; }
  if(good.size()==2 && good[0].second!=good[1].second){ printf("UNEQ\n"); bad=true; }
  long long tot=0; for(auto&g:good) tot+=g.second;
  return tot;
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){int x;scanf("%d",&x);pool[x]++;}
  long long a = dfs(0,0,0);
  printf("total0=%lld x2=%lld %s\n", a, a*2, bad?"BAD":"OK");
}
