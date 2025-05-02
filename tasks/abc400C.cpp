//* #pragma GCC optimize ("trapv")

#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

ll Sqrt(ll n) {
    ll x = sqrtl(n);
    while(x * x < n) x++;
    while(x * x > n) x--;
    return x;
}

using i128 = __int128;
void solve() {
    ll n; cin >> n;

    ll res = 0;
    for(i128 pot = 2; pot <= i128(n); pot *= 2LL) {
        i128 left = 1;
        i128 right = i128(1e9 + 1);
        while(left + 1 < right) {
            i128 middle = (left + right) >> 1LL;
            i128 cur = i128(2) * middle - i128(1);
            if(pot * cur * cur <= n) left = middle;
            else right = middle;
        }
        res += ll(left);
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
