#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define dbg(x) cout << #x << ": " << x << endl;
#define dbgs(x) cout << #x << ": " << x << ", ";
#define dbg(x) 0
#define dbgs(x) 0

void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;

    vl odds, evens;
    for(auto& x: a) {
        if(x & 1LL) odds.emplace_back(x);
        else evens.emplace_back(x);
    }
    sort(odds.begin(), odds.end());
    sort(evens.begin(), evens.end());

    ll re = 0;
    if(!odds.empty()) {
        re += accumulate(evens.begin(), evens.end(), 0LL);
        multiset<ll> ms;
        for(auto& x: odds) ms.emplace(x);
        while(!ms.empty()) {
            auto mx = *ms.rbegin();
            re += mx;
            ms.erase(ms.find(mx));
            if(ms.empty()) break;
            auto mn = *ms.begin();
            ms.erase(ms.find(mn));
        }
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--) {
        dbg("==================================");
        solve();
    }

    return 0;
}
