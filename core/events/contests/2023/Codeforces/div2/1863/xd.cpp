#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define nl "\n"

void solve(){
  string s; cin >> s;
  map<char, ll> m;
  for(int i=0;i<s.size();i++){
    m[s[i]] = i;
  }
  if(m['1'] > m['7']){
    cout << "71" << nl;
  }else{
    cout << "17" << nl;
  }
}

int main (){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
