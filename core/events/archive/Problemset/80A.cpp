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

const int MAXNUM = 100;
bool isPrime[MAXNUM];

void generateSieve() {
    for(int i = 0; i < MAXNUM; i++)
        isPrime[i] = true;

    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i < MAXNUM; i++)
        if(isPrime[i])
            for(int j = 2*i; j < MAXNUM; j += i)
                isPrime[j] = false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    int nextPrime = -1;
    for(int i = n + 1; i < MAXNUM; i++)
        if(isPrime[i]) {
            nextPrime = i;
            break;
        }

    cout << ((nextPrime == m)? "YES" : "NO");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    generateSieve();

    ll t = 1;

    while(t--)
        solve();

    return 0;
}
