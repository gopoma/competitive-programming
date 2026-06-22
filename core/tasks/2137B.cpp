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
    ll n; cin >> n;
    vl p(n); for(auto& x: p) cin >> x;
    vl q(n);
    for(int i = 0; i < n; i++) {
        q[i] = (n + 1) - p[i];
    }
    for(auto& x: q) cout << x << " ";
    cout << "\n";
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
