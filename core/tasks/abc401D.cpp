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

ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}

void solve() {
    ll n, k; cin >> n >> k;
    string S; cin >> S;

    ll cnt_o = 0;
    for(int i = 0; i < n; i++) {
        if(S[i] == 'o') {
            cnt_o++;
            if(0 <= i - 1) S[i - 1] = '.';
            if(i + 1 < n)  S[i + 1] = '.';
        }
    }
    dbg(n, k);
    dbg(S);


    vector<vl> G;
    vl C;
    for(int i = 0; i < n; i++) {
        if(S[i] == '?') {
            C.emplace_back(i);
        } else {
            if(!C.empty()) {
                G.emplace_back(C);
                C.clear();
            }
        }
    }

    if(!C.empty()) {
        G.emplace_back(C);
        C.clear();
    }
    dbg(G);

    ll mx_adi = 0;
    for(auto& vec: G) {
        mx_adi += cdiv(ll(sz(vec)), 2LL);
    }

    ll d = k - cnt_o;
    assert(d >= 0);
    if(d == 0) {
        dbg("d is zero", d);
        for(auto& c: S) {
            if(c == '?') {
                c = '.';
            }
        }
        cout << S << "\n";
        return;
    }

    dbg(d);
    dbg(mx_adi);
    if(d == mx_adi) {
        dbg("need all", d, mx_adi);
        for(auto& vec: G) {
            if((sz(vec)) % 2 == 0) {
                for(auto& i: vec) {
                    S[i] = '?';
                }
            } else {
                for(int j = vec.front(); j <= vec.back(); j += 2) {
                    S[j] = 'o';
                }
                for(int j = vec.front() + 1; j <= vec.back() - 1; j += 2) {
                    S[j] = '.';
                }
            }
        }
    } else {
        for(auto& vec: G) {
            for(auto& i: vec) {
                S[i] = '?';
            }
        }
    }

    dbg(S);
    cout << S << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1; //* cin >> t;
    while(t--) {
        solve();
        RAYA;
    }
}
