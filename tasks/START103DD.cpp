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

string norm(string& x) {
    assert(sz(x) >= 1);
    if(sz(x) == 1) {
        return "00" + x;
    } else if(sz(x) == 2) {
        return "0" + x;
    } else {
        return x;
    }
}

int calc_leadings(string s) {
    assert(sz(s) == 3);
    string t1 = s.substr(0, 3);
    string t2 = s.substr(0, 2);
    string t3 = s.substr(0, 1);
    if(t1 == "000") return 3;
    if(t2 == "00") return 2;
    if(t3 == "0") return 1;
    return 0;
}

void solve(string N, int n) {
    string tmp = N;
    vector<string> SS;
    for(int i = 0; i < 200; i++) {
        int multiple = 8 * i;
        if(multiple > 999) {
            break;
        }

        string partial = to_string(multiple);
        SS.eb(norm(partial));
    }

    N = norm(N);
    assert(sz(N) >= 3);

    int min_diffs = INT_MAX;
    string last_three = "$";
    for(auto& e: SS) {
        assert(sz(e) == 3);
        int diffs = 0;
        diffs += (N[sz(N) - 1] != e[2]);
        diffs += (N[sz(N) - 2] != e[1]);
        diffs += (N[sz(N) - 3] != e[0]);

        string pp = N.substr(sz(N) - 3, 3);
        int l1 = calc_leadings(pp);
        int l2 = calc_leadings(e);

        if(n <= 3 && l1 != l2) continue;

        if(diffs < min_diffs) {
            last_three = e;
            min_diffs = diffs;
        }
    }

    assert(min_diffs != INT_MAX);
    assert(last_three != "$");
    assert(sz(last_three) == 3);

    N[sz(N) - 1] = last_three[2];
    N[sz(N) - 2] = last_three[1];
    N[sz(N) - 3] = last_three[0];

    if(N[0] == '0') {
        N = N.substr(1, sz(N) - 1);
    }
    if(N[0] == '0') {
        N = N.substr(1, sz(N) - 1);
    }

    // DBG3(tmp, stoi(tmp) % 8, N);
    assert(sz(tmp) == sz(N));
    assert(N[0] != '0');
    cout << N << n_l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    cin >> t;

    while(t--) {
        int nn; string NN;
        cin >> nn >> NN;
        solve(NN, nn);

        // for(int i = 1; i < 1500; i++) {
        //     string tmp = to_string(i);
        //     solve(tmp, sz(tmp));
        // }
    }

    return 0;
}
