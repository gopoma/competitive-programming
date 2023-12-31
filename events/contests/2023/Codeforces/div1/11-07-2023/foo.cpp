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

ll mex(vector<ll> &arr, ll N) {
  // sort the array
  sort(arr.begin(), arr.end());

  ll mex = 1LL;
  for (ll idx = 0; idx < N; idx++)
  {
    if (arr[idx] == mex)
    {
      // Increment mex
      mex += 1LL;
    }
  }

  // Return mex as answer
  return mex;
}

bool isPrime(ll n)
{
    if (n <= 1LL)
        return false;

    for (ll i = 2LL; i * i <= n; i++)
    {
        if (n % i == 0LL)
            return false;
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;

    ll A[n];
    for(auto& a: A) cin >> a;

    ll ans = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            vector<ll> tmp;
            for(ll k = i; k <= j; k++) {
                tmp.push_back(A[k]);
            }
            if(isPrime(mex(tmp, SIZE(tmp)))) {
                ans++;
            }
        }
    }
    DBG(ans);
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
