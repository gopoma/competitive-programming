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
    ll n, k; cin >> n >> k;
    vl a(n); for(auto& x: a) cin >> x;

    map<ll, ll> mx;
    {
        map<ll, ll> hist;
        for(auto& x: a) {
            hist[x]++;
        }
        for(auto& [v, cnt]: hist) {
            if(cnt % k != 0) {
                cout << "0\n";
                return;
            }
            mx[v] = cnt / k;
        }
    }

    map<ll, ll> hist;
    set<ll> bads;
    auto add = [&](ll x) -> void {
        hist[x]++;
        if(hist[x] > mx[x]) {
            bads.emplace(x);
        }
    };
    auto check = [&]() -> bool {
        return bads.empty();
    };
    auto rem = [&](ll x) -> void {
        hist[x]--;
        if(hist[x] <= mx[x] && bads.count(x)) {
            bads.erase(bads.find(x));
        }
    };

    ll re = 0;
    ll left = 0;
    for(ll right = 0; right < n; right++) {
        add(a[right]);
        while(!check()) {
            rem(a[left]);
            left++;
        }
        assert(left <= right);
        re += right - left + 1LL;
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
