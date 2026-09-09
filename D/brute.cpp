// 暴力：枚举全部 2^n 个 01 序列，统计 p 值多重集等于输入的序列数。
#include <bits/stdc++.h>
using namespace std;
int main(){
  int n;
  scanf("%d",&n);
  vector<int> want(n);
  for(auto &x: want) scanf("%d",&x);
  sort(want.begin(), want.end());
  long long ans=0;
  int total = 1<<n;
  for(int mask=0; mask<total; mask++){
    vector<int> p(n);
    for(int i=0;i<n;i++){
      int cnt=0, bi=(mask>>i)&1;
      for(int j=0;j<=i;j++) if(((mask>>j)&1)!=bi) cnt++;
      p[i]=cnt;
    }
    sort(p.begin(), p.end());
    if(p==want) ans++;
  }
  printf("%lld\n", ans);
}
