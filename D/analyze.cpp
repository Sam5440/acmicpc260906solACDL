// 分析递归树：找出所有"有 ≥2 个成功子分支"的节点，打印其形态
#include <bits/stdc++.h>
using namespace std;
int n;
map<int,int> pool;
bool anyMulti=false;
// 返回从该状态出发的成功补全数
long long dfs(int SA, int SB, int turn, int depth){
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
    long long sub = (turn==0 ? dfs(SA+k, SB, 1, depth+1) : dfs(SA, SB+k, 0, depth+1));
    pool[v]+=k;
    it = pool.find(v);
    if(sub>0) good.push_back({k,sub});
  }
  if(good.size()>=2){
    // 检查形态是否为 {R, v-own}
    bool form = false;
    if(good.size()==2){
      int k1=good[0].first, k2=good[1].first;
      if((k1==v-own && k2==R)||(k2==v-own && k1==R)) form=true;
    }
    printf("MULTI depth=%d SA=%d SB=%d turn=%d v=%d R=%d good=[", depth, SA,SB,turn,v,R);
    for(auto&g:good) printf("(k=%d,c=%lld)",g.first,g.second);
    printf("] form12=%d\n", form);
    anyMulti=true;
  }
  long long tot=0; for(auto&g:good) tot+=g.second;
  return tot;
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){int x;scanf("%d",&x);pool[x]++;}
  long long a = dfs(0,0,0,0);
  printf("total(starting with 0)=%lld x2=%lld\n", a, a*2);
  if(!anyMulti) printf("no multi nodes\n");
}
