//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <cstdio> //? if you don't want IntelliSense
#include <algorithm>
using namespace std;

//* Template
//* /Template

int N;
int a[250000];
void solve() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    sort(a,a+N);
    if(N&1) printf("%.1f\n", float(a[N/2]));
    else {
        double ans = double((long long)(a[N/2])+(long long)(a[N/2-1]))/double(2);
        printf("%.1f\n", ans);
    }
}


signed main() {
    //? setIO();

    solve();
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
