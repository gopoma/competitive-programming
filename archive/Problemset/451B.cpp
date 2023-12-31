#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define F first
#define S second
#define SIZE(c) int((c).size())
#define ALL(c) begin(c), end(c)

typedef long long   ll;
typedef long double ld;

const char nl = '\n';

void solve() {
    int n;
    cin >> n;

    int a[n];
    for(auto& aa: a) cin >> aa;

    bool toReverse = false;
    int left = -1, right = -1;
    for(int i = 0; i < n - 1; i++) {
        if(toReverse && a[i] < a[i + 1]) {
            right = i;
            break;
        }
        if(!toReverse && a[i] > a[i + 1]) {
            toReverse = true;
            left = i;
        }
    }
    if(toReverse && right == -1) right = n - 1;

    if(toReverse) reverse(a + left, a + right + 1);

    if(is_sorted(a, a + n)) {
        cout << "yes" << nl;
        if(!toReverse) {
            left++;
            right++;
        }
        cout << (left+1) << " " << (right+1) << nl;
    }
    else cout << "no";
    cout << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
