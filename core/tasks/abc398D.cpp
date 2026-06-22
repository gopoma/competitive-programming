
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define dbg(x) cout << #x << ": " << x << endl;

void solve() {
    ll n, R, C; cin >> n >> R >> C;
    string S; cin >> S;

    map<char, pair<ll, ll>> D;
    D['N'] = {-1, 0};
    D['S'] = {+1, 0};
    D['E'] = {0, +1};
    D['W'] = {0, -1};

    set<pair<ll, ll>> aux;
    aux.emplace(0, 0);

    ll dx = 0;
    ll dy = 0;
    string re;
    for(auto& c: S) {
        dx += D[c].first;
        dy += D[c].second;

        // (dx, dy) - (x, y) = (R, C)
        // (x, y) = (dx, dy) - (R, C)
        ll x = dx - R;
        ll y = dy - C;

        if(aux.count({x, y})) re.push_back('1');
        else re.push_back('0');

        aux.emplace(dx, dy);
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
