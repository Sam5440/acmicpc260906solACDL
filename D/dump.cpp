#include <bits/stdc++.h>
using namespace std;
int n;
map<vector<int>, vector<string>> groups;
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
    groups[p].push_back(s);
    return;
  }
  s.push_back('0'); rec(s); s.pop_back();
  s.push_back('1'); rec(s); s.pop_back();
}
int main(){
  scanf("%d",&n);
  string s; rec(s);
  for(auto &kv: groups){
    printf("M=");
    for(int x: kv.first) printf("%d ", x);
    printf("| count=%d | ", (int)kv.second.size());
    for(auto &str: kv.second) printf("%s ", str.c_str());
    printf("\n");
  }
}
