// 生成一个保证有解的输入：随机生成 01 串，输出其 p 值多重集。
// 用法: ./gen_valid.exe n seed
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char**argv){
  int n = atoi(argv[1]);
  unsigned seed = atoi(argv[2]);
  mt19937 rng(seed);
  string s(n,'0');
  for(int i=0;i<n;i++) s[i] = '0' + (rng()&1);
  vector<int> p(n);
  for(int i=0;i<n;i++){
    int cnt=0;
    for(int j=0;j<=i;j++) if(s[j]!=s[i]) cnt++;
    p[i]=cnt;
  }
  printf("%d\n", n);
  for(int i=0;i<n;i++) printf("%d%c", p[i], " \n"[i==n-1]);
}
