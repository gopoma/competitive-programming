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

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define mp  make_pair
#define F   first
#define S   second

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

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

bool ok(vector<ll>& V, ll target) {
    set<ll> aux;
    for(auto& e: V) {
        if(e == target || aux.find(target - e) != aux.end()) {
            return true;
        } else {
            aux.ins(e);
        }
    }
    return false;
}

void solve() {
    vector<ll> aks1 = {1, -1, 2, 3};
    vector<ll> aks2 = {1, -1, 2, 3};
    assert(ok(aks1, 5));
    assert(!ok(aks2, -5));

    ll N, K, E;
    cin >> N >> K >> E;

    ll gap1 = E;
    ll gap2 = N - K - E;

    set<ll> gaps;
    gaps.ins(K);
    gaps.ins(gap1);
    gaps.ins(gap2);

    map<ll, ll> freq;
    freq[K]++;
    freq[gap1]++;
    freq[gap2]++;

    // DBG("GO");
    // for(auto& e: gaps) {
    //     cout << e << " ";
    // }
    // cout << n_l;
    // DBG("GO");

    if(sz(gaps) == 3) {
        cout << "0\n";
    } else if(sz(gaps) == 2) {
        ll repeated = -1LL;

        for(auto& it: freq) {
            if(it.second == 2LL) {
                repeated = it.first;
            }
        }
        assert(repeated != -1LL);



        vector<ll> allowable;
        for(ll i = 1LL; i <= N; i++) {
            if(gaps.find(i) == gaps.end() && i < repeated) {
                allowable.eb(i);
            }
        }

        // DBG(allowable);

        ll ans = 0LL;
        bool found = false;
        for(int i = 0; i <= repeated; i++) {
            ll target = repeated - i;
            map<ll, ll> aux;
            if(ok(allowable, target)) {
                ans += i;
                found = true;
                break;
            }
        }
        if(!found) ans = repeated;
        cout << ans << n_l;
    } else if(sz(gaps) == 1) {
        const ll repeated = K;

        // vector<ll> allowable;
        // for(ll i = 1LL; i <= N; i++) {
        //     if(gaps.find(i) == gaps.end() && i < repeated) {
        //         allowable.eb(i);
        //     }
        // }

        // DBG(allowable);

        if(repeated == 1LL) {
            // 1 1 1 -> 1 X 1
            cout << "2\n";
        } else if(repeated == 2LL) {
            // 2 2 2 -> 1 X 2
            cout << "3\n";
        } else if(repeated == 3LL) {
            // 3 3 3 -> X X 3
            cout << "3\n";
        } else if(repeated == 4LL) {
            // 4 4 4 -> X X 2
            cout << "2\n";
        } else if(repeated >= 5LL) {
            // 5 5 5 -> X X X
            cout << "0\n";
        }
    } else {
        assert(false);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
