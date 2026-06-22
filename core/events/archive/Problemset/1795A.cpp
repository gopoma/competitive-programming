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

bool ok(string s) {
    bool ans = true;
    for(int i = 0; i < SIZE(s)-1; i++)
        ans &= s[i]!=s[i+1];
    return ans;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    ll sr = 0, spos = -1;
    ll tr = 0, tpos = -1;
    for(ll i = 0; i < n-1; i++)
        if(s[i] == s[i+1]) { sr++; spos = i; }

    for(ll i = 0; i < m-1; i++)
        if(t[i] == t[i+1]) { tr++; tpos = i; }

    if(sr>1||tr>1||(sr==1&&tr==1)) {
        cout << "NO\n";
    } else {
        if(sr==0&&tr==0) {
            cout << "YES\n";
            return;
        }

        bool ans;
        string tmp, aux;
        if(sr == 1) {
            tmp = s.substr(spos+1, n-spos-1);
            reverse(ALL(tmp));
            ans = ok(t+tmp);
        } else {
            tmp = t.substr(tpos+1, m-tpos-1);
            reverse(ALL(tmp));
            ans = ok(s+tmp);
        }
        cout << (ans?"YES":"NO") << nl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
