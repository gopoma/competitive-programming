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

int score(vector<int>& perm) {
    unordered_set<int> aux;
    for(int i = 0; i < sz(perm)-1; i++)
        aux.ins(__gcd(perm[i], perm[i+1]));

    aux.ins(__gcd(perm[sz(perm)-1], perm[0]));

    return sz(aux);
}

void brute() {
    // 2 -> 1
    // 3 -> 1
    // 4 -> 2
    // 5 -> 2
    // 6 -> 3
    // 7 -> 3
    // 8 -> 4
    // 9 -> 4
    // 10 -> 5
    // 11 -> 5
    // 12 -> 6
    int n = 12;
    assert(n >= 2);

    vector<int> perm(n);
    for(int i = 1; i <= n; i++) {
        perm[i-1] = i;
    }

    int maxScore = 0;

    do {
        maxScore = max(maxScore, score(perm));
    } while(next_permutation(all(perm)));



    for(int i = 1; i <= n; i++) {
        perm[i-1] = i;
    }

    int count = 0;
    do {
        int sc = score(perm);
        if(sc == maxScore) {
            // for(auto& e: perm) {
            //     cout << e << " ";
            // }
            // cout << n_l;
            count++;
        }
    } while(next_permutation(all(perm)));

    DBG2(maxScore, count);
}

void solve() {
    int n;
    cin >> n;

    vector<int> ans;
    set<int> aux;
    for(int i = 2; 2*i <= n; i++) {
        if(aux.count(i)) continue;

        int current = i;
        while(current <= n) {
            ans.eb(current);
            aux.ins(current);
            current = 2*current;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(!aux.count(i)) {
            ans.eb(i);
        }
    }

    assert(sz(ans) == n);

    int sc = score(ans);
    assert(sc == n/2);

    for(auto& e: ans) {
        cout << e << " ";
    }
    cout << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        // brute();
        solve();
    }

    return 0;
}
