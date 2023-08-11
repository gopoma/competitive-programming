#include <bits/stdc++.h>
using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	for(int test_number = 0; test_number < t; test_number++){
		int n; cin >> n;
		vector <string> long_subs;
		for(int i = 0; i < 2 * n - 2; i++){
			string s;
			cin >> s;
			if((int)s.size() == n - 1){
				long_subs.push_back(s);
			}
		}
        DBG(long_subs[0]);
        DBG(long_subs[1]);
		reverse(long_subs[1].begin(), long_subs[1].end());
        DBG(long_subs[1]);
		if(long_subs[0] == long_subs[1]){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}

	return 0;
}
