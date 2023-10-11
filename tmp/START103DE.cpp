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

void solve() {
    // RAYA;
    int N, K;
    cin >> N >> K;

    string s;
    cin >> s;

    int ans0 = 0, ans1 = 0;
    bool ok1 = true;

    auto solve_single = [&](string& x) {
        assert(sz(x) >= 2);
        int zeros = 0;
        int ones = 0;

        for(char& c: x) {
            zeros += (c == '0');
            ones += (c == '1');
        }

        if(zeros == 0) { // 1111...1111
            assert(ones >= 2);
            ans0 += (ones % 2 == 0)? (ones / 2) : (3 + (ones - 3) / 2);
            ans1 += 0;
        } else if(ones == 0) { // 0000...0000
            ans0 += 0;
            ok1 = false;
        } else { // 10110100...00101
            assert(zeros >= 1 && ones >= 1);
            ans0 += (ones % 2 == 0)? (ones / 2) : (2 + (ones - 1) / 2);
            ans1 += zeros;
        }
    };

    for(int i = 0; i < K; i++) {
        string partial = "";
        for(int j = i; j < N; j += K) {
            partial += s[j];
        }

        solve_single(partial);
    }

    int global_ans;
    if(ok1) {
        global_ans = min(ans0, ans1);
    } else {
        global_ans = ans0;
    }

    cout << global_ans << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
