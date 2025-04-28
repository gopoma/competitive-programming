#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
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
//* /Debugger

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(x) << "\033[0m" << endl;
#define GA dbg(0)
#define RAYA   dbg("================================");

void solve() {
    ll n; cin >> n;
    string S; cin >> S;

    vl A, B;
    for(ll x = 1; x <= n; x++) {
        if(S[x - 1] == 'A') A.emplace_back(x);
        else B.emplace_back(x);
    }

    if(n == 2) {
        if(S == "AB") cout << "Alice\n";
        else cout << "Bob\n";
        return;
    }

    if(A.front() == 1 && A.back() == n) {
        cout << "Alice\n";
        return;
    }
    if(B.front() == 1 && B.back() == n) {
        cout << "Bob\n";
        return;
    }

    if(B.back() == n) {
        if(sz(B) >= 2) cout << "Bob\n";
        else cout << "Alice\n";
        return;
    } else {
        if(sz(A) >= 2 && A[sz(A) - 2] > B.back()) cout << "Alice\n";
        else cout << "Bob\n";
    }
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while(t--) {
        solve();
    }
}
