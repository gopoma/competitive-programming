#pragma GCC optimize ("Ofast")

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

#define dbg(x) 42
#define GA dbg(0)
#define RAYA   dbg("================================");

void solve() {
    ll n, k; cin >> n >> k;
    string S; cin >> S;
    ll q; cin >> q;
    V<string> queries(q);
    for(auto& it: queries) cin >> it;

    vector<int> where[26];
    for(int i = 0; i < n; i++) {
        where[S[i] - 'a'].emplace_back(i);
    }

    vector<int> dp(n, int(1e9));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < k; j++) {
            auto it = upper_bound(where[j].begin(), where[j].end(), i);
            if(it == where[j].end()) {
                dp[i] = 1;
            } else {
                dp[i] = min(dp[i], dp[*it] + 1);
            }
        }
    }
    dbg(dp);

    vector<int> res;
    for(auto& x: queries) {
        RAYA;
        dbg(x);
        const int N = sz(x);
        int cur = -1;
        bool should = true;
        for(int i = 0; i < N; i++) {
            auto it = upper_bound(where[x[i] - 'a'].begin(), where[x[i] - 'a'].end(), cur);
            if(it == where[x[i] - 'a'].end()) {
                res.emplace_back(0);
                should = false;
                dbg("rage quit");
                break;
            } else {
                cur = *it;
            }
        }
        if(should) {
            dbg(cur);
            dbg(dp[cur]);
            res.emplace_back(dp[cur]);
        }
    }

    for(auto& x: res) cout << x << "\n";
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    while(t--) {
        solve();
        RAYA;
    }
}
