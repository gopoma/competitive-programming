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

using ll = long long;
using ld = long long;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!

#define mp  make_pair
#define f   first
#define s   second

#define sz(x)   int((x).size())
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

void solve() {
    int n;
    cin >> n;

    int A[n]; for(auto& a: A) cin >> a;
    int B[n]; for(auto& b: B) cin >> b;
    bool mtx[n][n];
    for(int u = 0; u < n; u++)
    for(int v = 0; v < n; v++)
        mtx[u][v] = false;

    for(int u = 0; u < n; u++)
        for(int v = 0; v < n; v++) {
            if(u == v) continue;
            mtx[u][v] = (A[u]-A[v])>=(B[u]-B[v]);
        }

    cout << "Graph:\n";
    for(int u = 0; u < n; u++) {
        for(int v = 0; v < n; v++) {
            cout << mtx[u][v] << " ";
        }
        cout << n_l;
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
