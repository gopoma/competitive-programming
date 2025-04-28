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

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vl  A = {1, -2, 3, -4, 5, -6};
    V<long double>  B = {1.075, 2.75};
    V<pl> C = {make_pair(-25, 75), make_pair(79, 13)};
    map<ll, int> D; D[12]++; D[13] = ll(1e9) + 5;
    unordered_map<ll, int> E; E[12] = ll(1e9) + 5; E[13]++;
    set<ll> F; F.emplace(23); F.emplace(23); F.emplace(16);
    unordered_set<ll> G; G.emplace(23); G.emplace(23); F.emplace(16);
    multiset<ll> H; H.emplace(23); H.emplace(23); H.emplace(16);
    string I = "xd";

    dbg(C);

    const int n = 3;
    const int m = 4;
    const int k = 5;
    V<V<vl>> dp(n, V<vl>(m, vl(k)));

    array<int, 4> ndp = {1, 2, 3, 4};

    dbg(A);
    dbg(B);
    dbg(dp);
    dbg(1);
    dbg("dhuamanilu");
    GA;
    dbg(ndp);
    RAYA;
    set<int> xd;
    for(int x = 1; x <= 10; x++) xd.emplace(x);
    dbg(xd);

    map<pair<int, int>, vector<int>> mp;
    mp[make_pair(1, 2)].emplace_back(1);
    mp[make_pair(1, 2)].emplace_back(2);
    mp[make_pair(1, 2)].emplace_back(3);
    mp[make_pair(1, 2)].emplace_back(4);
    pair<vector<int>, vector<int>> pm;
    vector<int> tmp{1, 2, 3};
    vector<int> tmp2{4, 5, 6};
    pm = make_pair(tmp, tmp2);
    dbg(mp);
    dbg(pm);
}
