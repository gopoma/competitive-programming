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

bool hasSameDigits(int N) {
    int length = int(log10(N)) + 1;
    int M = (int(pow(10, length)) - 1) / (10 - 1);
    M *= N % 10;

    return M == N;
}

void solve() {
    int n;
    cin >> n;

    string strn = to_string(n);
    int amountDigits = SIZE(strn);
    int first = stoi(strn.substr(0, 1));
    string firstGeneratedStr = "";
    for(int i = 0; i < amountDigits; i++) firstGeneratedStr += to_string(first);
    int firstGenerated = stoi(firstGeneratedStr);
    cout << (9*(amountDigits-1)+(first-1+(firstGenerated<=n))) << nl;
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
