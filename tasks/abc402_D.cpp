#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

#define dbg(x) cout << "Line(" << __LINE__ << "): " << #x << ": " << x << endl;
#define GA     debug(0)
#define RAYA   cout << "================================" << endl;

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m; cin >> n >> m;
    vector<pair<ll, ll>> a(m);
    for(auto& [x, y]: a) cin >> x >> y;

    map<ll, ll> hist;
    for(auto& [x, y]: a) hist[x + y]++;

    ll res = ((m - 1) * m) / 2LL;
    map<ll, ll> vis;
    for(auto& [sum, _]: hist) {
        if(vis[sum]) continue;
        vis[sum] = true;
        vis[sum + n] = true;

        ll cnt = hist[sum] + hist[sum + n];
        res -= ((cnt - 1) * cnt) / 2LL;
    }
    cout << res << "\n";
}
