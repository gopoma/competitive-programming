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
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    a.emplace_back(0); n++;
    dbg(n);
    dbg(a);
    vl suff_sum = a;
    for(int i = n - 2; i >= 0; i--) suff_sum[i] += suff_sum[i + 1];
    vl pref_max = a;
    for(int i = 1; i < n; i++) pref_max[i] = max(pref_max[i], pref_max[i - 1]);
    dbg(a);
    dbg(suff_sum);
    dbg(pref_max);
    vl res(n - 1);
    for(int i = n - 2; i >= 0; i--) {
        ll A = suff_sum[i];
        ll B = pref_max[i] + suff_sum[i + 1];
        res[i] = max(A, B);
    }
    reverse(res.begin(), res.end());
    for(auto& x: res) cout << x << " ";
    cout << "\n";
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while(t--) {
        solve();
        RAYA;
    }
}
