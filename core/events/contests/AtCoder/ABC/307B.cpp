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

bool isPalindrome(string s) {
    for(ll i = 0; i < SIZE(s)/2; i++)
        if(s[i] != s[SIZE(s) - i - 1])
            return false;
    return true;
}

void solve() {
    ll N;
    cin >> N;

    string S[N];
    for(auto& s: S) cin >> s;

    bool ok = false;
    for(ll i = 0; i < N; i++) {
        for(ll j = i+1; j < N; j++) {
            if(isPalindrome(S[i]+S[j]) || isPalindrome(S[j]+S[i])) {
                ok = true;
                break;
            }
        }
    }

    cout << (ok?"Yes":"No") << nl;
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
