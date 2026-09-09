// 检验：成功分支集合 G 是否恰好等于“局部候选集” C
// k in [1,R]: (i) k==R 或 own+k<=v；(ii) 取完后若池非空，需 pool[own+k]>=1
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
  vector<int> good, cand;
  for(int k=1;k<=R;k++){
    bool ci = (k==R) || (own+k<=v);
    bool cii = false;
    if(ci){
      // 模拟取 k 份后的池子
      bool emptyAfter = (k==R && pool.size()==1);
      if(emptyAfter) cii = true;
      else {
        int rem = R - k;
        if(own+k==v){ cii = rem>=1; }
        else { auto jt=pool.find(own+k); cii = (jt!=pool.end()); }
      }
    }
    if(ci&&cii) cand.push_back(k);
    it->second -= k;
    if(it->second==0) pool.erase(it);
    long long sub = (turn==0 ? dfs(SA+k, SB, 1) : dfs(SA, SB+k, 0));
    pool[v]+=k;
    it = pool.find(v);
    if(sub>0) good.push_back(k);
  }
  sort(good.begin(),good.end()); sort(cand.begin(),cand.end());
  if(good!=cand){
    printf("DIFF SA=%d SB=%d turn=%d v=%d R=%d good=[",SA,SB,turn,v,R);
    for(int k:good)printf("%d,",k);
    printf("] cand=[");
    for(int k:cand)printf("%d,",k);
    printf("]\n");
    bad=true;
  }
  long long tot=0;
  return (long long)good.size(); // 只看结构
}
int main(){
  scanf("%d",&n);
  for(int i=0;i<n;i++){int x;scanf("%d",&x);pool[x]++;}
  dfs(0,0,0);
  printf("%s\n", bad?"BAD":"OK");
}
