#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;
using str = string;

using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
mt19937 rng(0);

ll rng_ll(ll L, ll R) {
    assert(L <= R);
    return uniform_int_distribution<ll>(L, R)(rng);
}

template<class T> void shuf(vector<T>& v) {
    shuffle(all(v), rng);
}


#define dbg(x) cout << #x << ": " << x << endl
// #define dbg(x) 0
#define RAYA dbg("===========================")
template<class T> void pvec(vector<T> v) {
    for(auto& x: v) cout << x << " ";
    cout << "\n";
}


void solve() {
    ll a, b; cin >> a >> b;
    ll twos = 0;
    ll A = a, B = b;

    if(A % 2 == 0 && B % 2 == 1) {
        cout << "-1\n";
        return;
    }

    while(A % 2 == 0) {
        twos++;
        A /= 2LL;
    }
    while(B % 2 == 0) {
        twos++;
        B /= 2LL;
    }
    ll re = 0;
    if(twos == 0) {
        re = a * b + 1LL;
    } else if(twos == 1) {
        re = -1;
    } else {
        re = 2LL + (a * b) / 2LL;
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
