#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) cout << "Line(" << __LINE__ << "): " << #x << ": " << x << endl;
#define GA     debug(0)
#define RAYA   cout << "================================" << endl;

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

ll rangeXOR(ll n) {
    if(n < 0) return 0;

    if (n % 4 == 0)
        return n;

    if (n % 4 == 1)
        return 1;

    if (n % 4 == 2)
        return n + 1LL;

    return 0;
}

ll rangeXOR(ll l, ll r) {
    return rangeXOR(r) ^ rangeXOR(l - 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll A, B; cin >> A >> B;
    ll res = rangeXOR(A, B);
    cout << res << "\n";
}
