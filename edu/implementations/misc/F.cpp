#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    ll N, M;
    cin >> N >> M;

    ll L[N];
    for(ll i = 0; i < N; i++)
        cin >> L[i];

    multiset<ll> diffs;
    for(ll i = 0; i < N - 1; i++) {
        diffs.insert(L[i+1] - L[i]);
    }

    for(ll i = 0; i < M; i++) {
        ll maxdiff = *diffs.rbegin();
        if(maxdiff == 1) {
            break;
        } else {
            diffs.insert(maxdiff/2);
            diffs.insert(ceil(maxdiff/2.0));
            diffs.erase(diffs.find(maxdiff));
        }
    }

    cout << (*diffs.rbegin()) << "\n";

    return 0;
}
