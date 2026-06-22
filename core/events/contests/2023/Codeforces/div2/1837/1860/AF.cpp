
#include <bits/stdc++.h>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define ll long long

void solve(){
  string s; cin >> s;
  int n = s.size();
  // ()
  // (())
  // ()()
  string ans1 = "";
  string ans2 = "";
  string ans3 = "";
  for(int i = 0; i < 2*n ;i+=2){
    ans1 += "()";
    ans2 = "(" + ans2 + ")";
  }
  bool turno = true;
  for(int i = 0; i < 2*n; i+=2){
    if(turno){
      ans3 += "()";
    }else{
      ans3 = "(" + ans3 + ")";
    }
    turno &= false;
  }
  DBG3(ans1, ans2, ans3);
  bool flag1 = false;
  bool flag2 = false;
  bool flag3 = false;
  for(int i = 0; i < n; i++){
    if(ans1.substr(i, n) == s){
        DBG2(ans1, ans1.substr(i, n));
      flag1 = true;
    }
    if(ans2.substr(i, n) == s){
      flag2 = true;
    }
    if(ans3.substr(i, n) == s){
      flag3 = true;
    }
  }
  if(flag1 && flag2 && flag3){
    cout << "NO\n";
  }else if(flag1 == false){
    cout << "YES\n";
    cout << ans1 << "\n";
  }else if(flag2 == false){
    cout << "YES\n";
    cout << ans2 << "\n";
  }else{
    cout << "YES\n";
    cout << ans3 << "\n";
  }
}

int main (){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
