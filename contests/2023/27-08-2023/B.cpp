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


bool canBeBalanced(string sequence) {
    if (sequence.size() & 1)
        return false;
 
    stack<char> stack_, stack2_;
 
    int countOpen = 0, countClosed = 0;
    int countSymbol = 0;
 
    for (int i = 0; i < int(sequence.size()); i++) {
        if (sequence[i] == ')') {
            countClosed++;

            if (stack_.empty()) {
                return false;
            }
 
            else {
                stack_.pop();
            }
        }
 
        else {
            if (sequence[i] == '?') countSymbol++;
            else countOpen++;
            stack_.push(sequence[i]);
        }
    }
 
    for (int i = int(sequence.size() - 1); i >= 0; i--) {
        if (sequence[i] == '(') {
            if (stack2_.empty())
                return false;
            else
                stack2_.pop();
        }
        else {
            stack2_.push(sequence[i]);
        }
    }
 
    int extra = abs(countClosed - countOpen);
 
    if (countSymbol < extra)
        return false;
 
    else {
        countSymbol -= extra;
 
        if (countSymbol % 2 == 0) {
            return true;
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;

    str s;
    cin >> s;

    if(n & 1) cout << ":(\n";
    else {
        assert(n >= 2);
        bool komp = (s[0] == '(' && s[1] == ')') || (s[0] == '(' && s[1] == '?') || (s[0] == '?' && s[1] == ')') || (s[0] == '?' && s[1] == '?');
        if(!komp) {
            cout << ":(\n";
        } else {
            string rem = s.substr(1, n - 2);

            if(rem == "") {
                cout << "()\n";
            } else {
                bool ok = canBeBalanced(rem);

                if(!ok) cout << ":(\n";
                else {
                    int openings = 0, closeds = 0, questions = 0;
                    for(auto& c: rem) {
                        openings += (c == '(');
                        closeds += (c == ')');
                        questions += (c == '?');
                    }
                    int maxoc = max(openings, closeds);
                    int shouldOpenIncrease = abs(maxoc - openings);

                    str ans = "(";
                    ans += ")";
                }
            }
        }
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
