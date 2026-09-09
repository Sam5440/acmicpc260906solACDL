#include <bits/stdc++.h>
using namespace std;
int n;
map<vector<int>, int> groups;
void rec(string &s){
  int m = s.size();
  if(m == n){
    vector<int> p(n);
    for(int i=0;i<n;i++){
      int cnt=0;
      for(int j=0;j<=i;j++) if(s[j]!=s[i]) cnt++;
      p[i]=cnt;
    }
    sort(p.begin(), p.end());
    groups[p]++;
    return;
  }
  s.push_back('0'); rec(s); s.pop_back();
  s.push_back('1'); rec(s); s.pop_back();
}
int main(){
  scanf("%d",&n);
  string s; rec(s);
  for(auto &kv: groups){
    int c = kv.second, b=0, x=c;
    while(x%2==0){x/=2;b++;}
    printf("b=%d(c=%d) M=", b-1, c); // b-1: 去掉起始比特的那一个 2
    for(int v: kv.first) printf("%d ", v);
    if(x!=1) printf("  <<< NOT POW2");
    printf("\n");
  }
}
