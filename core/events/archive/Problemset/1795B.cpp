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

const int MAXN = 100;
int arr[MAXN];

void solve() {
    int n, k;
    cin >> n >> k;

    for(auto& a: arr) a = 0;

    vector<pair<ll, ll>> s(n);
    for(auto& it: s)
        cin >> it.F >> it.S;

    for(auto& it: s) {
        if(it.F <= k && k <= it.S) {
            for(int i = it.F; i <= it.S; i++) {
                arr[i]++;
            }
        }
    }

    int maxe = *max_element(arr, arr+MAXN);

    bool maxIsK = arr[k] == maxe;
    int amountMax = 0;

    for(int i = 1; i < MAXN; i++) {
        if(arr[i] == maxe) {
            amountMax++;
        }
    }

    if(maxIsK && amountMax == 1) cout << "YES";
    else cout << "NO";
    cout << "\n";
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
