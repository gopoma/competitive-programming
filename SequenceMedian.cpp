//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <stdio.h> //? if you don't want IntelliSense
#include <algorithm>
#include <set>
using namespace std;

//* Template
//* /Template

#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int N;
int a[250002];
void solve() {
    N = read();
    multiset<int> ms;
    for(int i = 0; i < N; i++) {
        int act = read();
        ms.emplace(act);
        if(ms.size() > N/2) continue;
    }
}


signed main() {
    solve();
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
