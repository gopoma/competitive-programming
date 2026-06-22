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
    ll N;
    cin >> N;

    vector<string> votes(N);
    for(auto& v: votes) cin >> v;

    map<string, ll> count;
    unordered_set<string> diferentes;
    for(auto& v: votes) {
        count[v]++;
        diferentes.insert(v);
    }

    ll maxc = 0;
    for(auto& it: count) {
        maxc = max(maxc, it.S);
    }

    set<string> ans;
    if(maxc > (N/2)) {
        for(auto& it: count) {
            if(it.S != maxc) {
                ans.insert(it.F);
            }
        }
    } else {
        bool canContinue = true;
        while(canContinue) {
            set<string> parcial;

            ll minc = LLONG_MAX;
            for(auto& it: count) {
                if(!ans.count(it.F)) {
                    minc = min(minc, it.S);
                }
            }

            ll acc = 0;
            for(auto& it: count) {
                if(!ans.count(it.F) && it.S == minc) {
                    parcial.insert(it.F);
                    acc += it.S;
                }
            }

            for(auto& p: parcial) ans.insert(p);

            if(SIZE(ans) == SIZE(diferentes)) break;

            for(auto& it: count) {
                if(!ans.count(it.F)) {
                    canContinue &= ((it.S + acc) <= (N/2));
                }
            }
        }
    }

    cout << SIZE(ans) << nl;
    for(auto& e: ans) {
        cout << e << nl;
    }
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
