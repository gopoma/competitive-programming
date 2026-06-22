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

void solve(ll num_case) {
    // RAYA;

    int N; cin >> N;
    str s; cin >> s;

    int Q; cin >> Q;
    vector<int> B(Q);
    for(auto& b: B) {
        cin >> b;
    }

    vector<int> FB;
    set<int> aux;
    for(int i = 0; i < Q; i++) {
        bool found = aux.find(B[i]) != aux.end();
        if(found) {
            aux.erase(B[i]);
        } else {
            aux.ins(B[i]);
        }
    }

    for(auto& e: aux) {
        FB.eb(e);
    }

    // DBG(FB);
    for(int i = 0; i < sz(FB); i++) {
        for(int j = FB[i] - 1; j < N; j += FB[i]) {
            s[j] = (s[j] == '0') ? '1' : '0';
        }
    }
    // DBG(s);

    int ans = 0;
    for(int i = 0; i < sz(s); i++) {
        if(s[i] == '1') {
            ans++;
            for(int j = i; j < sz(s); j += (i + 1)) {
                s[j] = (s[j] == '0') ? '1' : '0';
            }
        }
    }

    cout << "Case #" << num_case << ": " << ans << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T = 1LL;
    cin >> T;

    for(ll i = 1LL; i <= T; i++) {
        solve(i);
    }

    return 0;
}
