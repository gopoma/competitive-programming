// sometimes pragmas don't work
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

#define sz(x)   int((x).size())
#define all(x)  x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define ins     insert
#define pb      push_back
#define eb      emplace_back

const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

/*Returns true if s1 is subsequence of s2*/
bool is_subsequence(string& s1, string& s2)
{
    assert(sz(s1) <= sz(s2));
    int n = s1.length(), m = s2.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s1[i] == s2[j])
            i++;
        j++;
    }
    /*If i reaches end of s1,that mean we found all
    characters of s1 in s2,
    so s1 is subsequence of s2, else not*/
    return i == n;
}

void solve() {
    int N;
    string Tmodificado;

    cin >> N >> Tmodificado;
    // DBG2(N, Tmodificado);

    vector<int> res;
    for(int i = 1; i <= N; i++) {
        string T;
        cin >> T;

        // DBG2(T, Tmodificado);

        bool ok = false;
        if(T == Tmodificado) {
            ok = true;
        } else if((Tmodificado.size() == (T.size() + 1)) && is_subsequence(T, Tmodificado)) {
            ok = true;
        } else if(((Tmodificado.size() + 1) == T.size()) && is_subsequence(Tmodificado, T)) {
            ok = true;
        } else if(Tmodificado.size() == T.size()) {
            int diffs = 0;
            for(int j = 0; j < Tmodificado.size(); j++) {
                diffs += (Tmodificado[j] != T[j]);
            }

            if(diffs == 1) {
                ok = true;
            }
        }

        if(ok) {
            res.eb(i);
        }
    }

    cout << sz(res) << n_l;
    for(int i = 0; i < sz(res); i++) {
        cout << res[i] << " \n"[i == sz(res) - 1];
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
